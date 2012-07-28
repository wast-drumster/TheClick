/*
** Copyright (C) 2012 Sebastian Roeglinger <wast.drumster@gmail.com>
** 
** This file is part of TheClick.
** 
** TheClick is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** TheClick is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with TheClick.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "libTheClick/ClickGenerator/ClickGenerator_DivisionSubdivision.h"
#include "libTheClick/definitions.h"
#include "libTheClick/SoundBase.h"

#include <stdexcept>

#include "boost/bind.hpp"

//DEBUG
//#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    ClickGenerator_DivisionSubdivision::ClickGenerator_DivisionSubdivision()
    {
        //initialize
        this->clickConfiguration = NULL;
        this->amountDivisions = 4;
        this->amountSubdivisions = 6;
        
        for(int32_t i = 0; i<DIVSUBDIV__MAX_DIVISIONS; i++)
            this->divisionPattern[i] = NULL;
        
        for(int32_t i = 0; i<DIVSUBDIV__MAX_SUBDIVISIONS; i++)
            this->subdivisionPattern[i] = NULL;

        //create divisionCallBackThread
        this->divisionCallbackThreadShouldStop = false;
        this->divisionCallbackThread = new boost::thread( boost::bind( &ClickGenerator_DivisionSubdivision::divisionCallbackWorkerFunction, &(*this) ) );
        
        
        //reset
        this->reset();
    }
    
    ClickGenerator_DivisionSubdivision::~ClickGenerator_DivisionSubdivision()
    {
        //stop divisionCallbackThread
        this->divisionCallbackThreadShouldStop = true;
        this->divisionCallbackThread->join();
        delete this->divisionCallbackThread;
        
        //delete attributes
        for(int32_t i = 0; i<DIVSUBDIV__MAX_DIVISIONS; i++)
        {
            if(this->divisionPattern[i] != NULL)
                delete this->divisionPattern[i];
        }
        
        for(int32_t i = 0; i<DIVSUBDIV__MAX_SUBDIVISIONS; i++)
        {
            if(this->subdivisionPattern[i] != NULL)
                delete this->subdivisionPattern[i];
        }
    }
    
    //*****************************
    //********** METHODS **********
    //*****************************
    void ClickGenerator_DivisionSubdivision::reset()
    {
        //reset attributes
        this->lastBeatTime = 0;
        this->soundElementGenerationHasStarted = false;
        
        //remove all elements in soundElementList
        for (std::list<SoundElement*>::iterator it=this->soundElementList.begin(); it != this->soundElementList.end(); /*nothing*/)
        {
            delete *it;
            it = this->soundElementList.erase(it);
        } 
    }
   
    int32_t ClickGenerator_DivisionSubdivision::getAmountDivisions() const
    {
        return this->amountDivisions;
    }
    
    int32_t ClickGenerator_DivisionSubdivision::getAmountSubdivisions() const
    {
        return this->amountSubdivisions;
    }
    
    void ClickGenerator_DivisionSubdivision::setAmountDivisions(int32_t value)
    {
        //check correctnes
        if(value <= 0)
            throw std::logic_error("Divisions must be positive.");
        
        if(value > DIVSUBDIV__MAX_DIVISIONS)
            throw std::logic_error("Divisions must lower than DIVSUBDIV__MAX_DIVISIONS.");
        
        //take value
        this->amountDivisions = value;
    }
    
    void ClickGenerator_DivisionSubdivision::setAmountSubdivisions(int32_t value)
    {
        //check correctnes
        if(value <= 0)
            throw std::logic_error("Subdivisions must be positive.");
        
        if(value > DIVSUBDIV__MAX_SUBDIVISIONS)
            throw std::logic_error("Divisions must lower than DIVSUBDIV__MAX_SUBDIVISIONS.");
        
        //take value
        this->amountSubdivisions = value;
    }
    
    SoundElement* ClickGenerator_DivisionSubdivision::getDivisionPattern(int32_t pos) const
    {
        //check correctnes
        if(pos < 0 || pos > DIVSUBDIV__MAX_DIVISIONS-1)
            throw std::out_of_range("pos has to be between 0 and DIVSUBDIV__MAX_DIVISIONS-1");
        
        //return
        return this->divisionPattern[pos];
    }
    
    SoundElement* ClickGenerator_DivisionSubdivision::getSubdivisionPattern(int32_t pos) const
    {
        //check correctnes
        if(pos < 0 || pos > DIVSUBDIV__MAX_SUBDIVISIONS-1)
            throw std::out_of_range("pos has to be between 0 and DIVSUBDIV__MAX_SUBDIVISIONS-1");
        
        //return
        return this->subdivisionPattern[pos];    
    }
    
    void ClickGenerator_DivisionSubdivision::setDivisionPattern(int32_t pos, SoundElement* se)
    {
        //check correctnes
        if(pos < 0 || pos > DIVSUBDIV__MAX_DIVISIONS-1)
            throw std::out_of_range("pos has to be between 0 and DIVSUBDIV__MAX_DIVISIONS-1");
        
        //delete old SoundElement
        if(this->divisionPattern[pos] != NULL)
            delete this->divisionPattern[pos];
        
        //take value
        this->divisionPattern[pos] = se;
    }
    
    void ClickGenerator_DivisionSubdivision::setSubdivisionPattern(int32_t pos, SoundElement* se)
    {
        //check correctnes
        if(pos < 0 || pos > DIVSUBDIV__MAX_SUBDIVISIONS-1)
            throw std::out_of_range("pos has to be between 0 and DIVSUBDIV__MAX_SUBDIVISIONS-1");
        
        //delete old SoundElement
        if(this->divisionPattern[pos] != NULL)
            delete this->subdivisionPattern[pos];
        
        //take value
        this->subdivisionPattern[pos] = se;    
    }
    
    void ClickGenerator_DivisionSubdivision::generateSoundElements(int64_t endTime)
    {
        //calculate first beatIndex
        int32_t beatIndex = 0;
        if(this->soundElementGenerationHasStarted)
            beatIndex = (this->clickConfiguration->getReferenceBeatCount() + 1 + (this->lastBeatTime - this->clickConfiguration->getReferenceTime()) / this->clickConfiguration->getFramesPerBeat()) % this->amountDivisions;
        
        while(this->lastBeatTime < endTime)
        {
            //calculate nextBeatTime
            int64_t nextBeatTime = 0;
            if(this->soundElementGenerationHasStarted)
                 nextBeatTime = this->lastBeatTime + this->clickConfiguration->getFramesPerBeat();
            
            //debug
            //std::cout << "nextBeatTime: " << nextBeatTime << std::endl;
            
            //add SoundElements for beat (main division) and subdivisions
            if(this->divisionPattern[beatIndex] != NULL && this->divisionPattern[beatIndex]->getVolume() > 0.0f)
            {
                //add sound for beat (main division)
                SoundElement* seBeat = this->divisionPattern[beatIndex]->cloneAndSetTime(nextBeatTime);
                seBeat->setPlaybackCallback( boost::bind( &ClickGenerator_DivisionSubdivision::playbackCallbackDevision, &(*this), beatIndex, 0, _1, _2) );
                this->soundElementList.push_back(seBeat);
                
                //add sounds for subdivisions
                for(int32_t i = 1; i<this->amountSubdivisions; i++)
                {
                    if(this->subdivisionPattern[i] != NULL)
                    {
                        int64_t nextSubdevisionTime = nextBeatTime + i * this->clickConfiguration->getFramesPerBeat() / this->amountSubdivisions;
                        
                        //debug
                        //std::cout << "nextSubdevisionTime: " << nextSubdevisionTime << std::endl;
                        
                        SoundElement* seSubdev = this->subdivisionPattern[i]->cloneAndSetTime(nextSubdevisionTime);
                        seSubdev->setPlaybackCallback( boost::bind( &ClickGenerator_DivisionSubdivision::playbackCallbackDevision, &(*this), beatIndex, i, _1, _2) );
                        this->soundElementList.push_back(seSubdev);
                        
                        //debug
                        //std::cout << "size: " << this->soundElementList.size() << std::endl;
                    }
                }
            }
            
            //increment lastBeatTime
            this->lastBeatTime = nextBeatTime;
            
            //increment beatIndex
            beatIndex = (beatIndex + 1) % this->amountDivisions;
            
            //indicate that SoundElement generation has started
            this->soundElementGenerationHasStarted = true;
        }
    }
    
    void ClickGenerator_DivisionSubdivision::setClickConfiguration(ClickConfiguration* cc)
    {
        this->clickConfiguration = cc;
        this->lastBeatTime = cc->getReferenceTime();
        this->cleanSoundElements();
    }
    
    ClickConfiguration* ClickGenerator_DivisionSubdivision::getClickConfiguration()
    {
        return this->clickConfiguration;
    }
    
    std::list<SoundElement*>* ClickGenerator_DivisionSubdivision::getSoundElementList(int64_t time)
    {
        //generate new elements for the future in soundElementList
        this->generateSoundElements( time );
        
        //remove old elements in soundElementList
        //this->cleanSoundElementList();
        
        //return list
        return &this->soundElementList;
    }
    
    void ClickGenerator_DivisionSubdivision::cleanSoundElements()
    {
        //remove all elements in soundElementList which start in future
        for (std::list<SoundElement*>::iterator it=this->soundElementList.begin(); it != this->soundElementList.end(); /*nothing*/)
        {
            if( (*it)->time >= this->clickConfiguration->getReferenceTime() )
            {
                delete *it;
                it = this->soundElementList.erase(it);
            }
            else
            {
                it++;
            }
            
            //end condition
            if(it == this->soundElementList.end()) break;
        }
        
        //reset lastBeatTime
        if(this->soundElementGenerationHasStarted)
            this->lastBeatTime = this->clickConfiguration->getReferenceTime() - this->clickConfiguration->getFramesPerBeat();
    }
    
    void ClickGenerator_DivisionSubdivision::playbackCallbackDevision(int32_t division, int32_t subdivision, double timeStamp, boost::function<double(void)> timeFuncPointer )
    {
        divisionCallbackStruct* s = new divisionCallbackStruct;
        s->division = division;
        s->subdivision = subdivision;
        s->timeStamp = timeStamp;
        s->timeFuncPointer = timeFuncPointer;
        this->beatCountCallbackStructList.push_back(s);
    }
    
    void ClickGenerator_DivisionSubdivision::divisionCallbackWorkerFunction()
    {
        //run until object should be deleted
        while( !this->divisionCallbackThreadShouldStop )
        {
            //sleep
            boost::this_thread::sleep( boost::posix_time::milliseconds(20) );
            
            if(!this->beatCountCallbackStructList.empty() &&
               this->divisionCallbackFunction != NULL)
            {
                //delete elements in beatCountCallbackStructList
                for(std::list<divisionCallbackStruct*>::iterator it = this->beatCountCallbackStructList.begin(); it!=this->beatCountCallbackStructList.end(); /*nothing*/)
                {
                    if( (*it)->timeStamp <= (*it)->timeFuncPointer() )
                    {
                        //remove element from list
                        divisionCallbackStruct* s = *it;
                        it = this->beatCountCallbackStructList.erase(it);
                        
                        //call callback function
                        this->divisionCallbackFunction(s->division, s->subdivision);
                        
                        //delete element
                        delete s;
                    }
                    else
                    {
                        it++;
                    }
                }
            }
        }
    }

    
} //namespace libTheClick
