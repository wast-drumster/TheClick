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

#include "libTheClick/ClickGenerator/ClickGenerator_XoverY.h"
#include "libTheClick/definitions.h"
#include "libTheClick/SoundBase.h"

#include "boost/bind.hpp"

#include <stdexcept>

//DEBUG
//#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    ClickGenerator_XoverY::ClickGenerator_XoverY()
    {
        //initialize
        this->clickConfiguration = NULL;
        this->x = 3;
        this->y = 4;
        
        this->xSoundElement = NULL;
        this->ySoundElement = NULL;
        
        //create beatCallBackThread
        this->xCountCallbackThreadShouldStop = false;
        this->xCountCallbackThread = new boost::thread( boost::bind( &ClickGenerator_XoverY::xCountCallbackWorkerFunction, &(*this) ) );

        //reset
        this->reset();
    }
    
    ClickGenerator_XoverY::~ClickGenerator_XoverY()
    {
        //stop xCountCallbackThread
        this->xCountCallbackThreadShouldStop = true;
        this->xCountCallbackThread->join();
        delete this->xCountCallbackThread;
        
        //delete attributes
        if(this->xSoundElement != NULL)
            delete this->xSoundElement;

        if(this->ySoundElement != NULL)
            delete this->ySoundElement;
    }
    
    //*****************************
    //********** METHODS **********
    //*****************************
    void ClickGenerator_XoverY::reset()
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
    
    int32_t ClickGenerator_XoverY::getX() const
    {
        return this->x;
    }
    
    int32_t ClickGenerator_XoverY::getY() const
    {
        return this->y;
    }
    
    void ClickGenerator_XoverY::setX(int32_t value)
    {
        //check correctnes
        if(value <= 0)
            throw std::logic_error("X must be positive.");
        
        //take value
        this->x = value;
    }
    
    void ClickGenerator_XoverY::setY(int32_t value)
    {
        //check correctnes
        if(value <= 0)
            throw std::logic_error("Subdivisions must be positive.");
        
        //take value
        this->y = value;
    }
    
    SoundElement* ClickGenerator_XoverY::getXSoundElement() const
    {
        return this->xSoundElement;
    }
    
    SoundElement* ClickGenerator_XoverY::getYSoundElement() const
    {
        return this->ySoundElement;
    }
    
    void ClickGenerator_XoverY::setXSoundElement(SoundElement* se)
    {
        if(this->xSoundElement != NULL)
            delete this->xSoundElement;
        
        this->xSoundElement = se;
    }
    
    void ClickGenerator_XoverY::setYSoundElement(SoundElement* se)
    {
        if(this->ySoundElement != NULL)
            delete this->ySoundElement;
        
        this->ySoundElement = se;    
    }
    
    void ClickGenerator_XoverY::generateSoundElements(int64_t endTime)
    {
        //calculate amount of beats
        int32_t beats = 0;
        if(this->soundElementGenerationHasStarted)
            beats = this->clickConfiguration->getReferenceBeatCount() + 1 + (this->lastBeatTime - this->clickConfiguration->getReferenceTime()) / this->clickConfiguration->getFramesPerBeat();
        
        int32_t x = (beats * this->y) % this->x;
        
        //fill SoundElementList
        while(this->lastBeatTime < endTime)
        {
            //calculate nextBeatTime
            int64_t nextBeatTime = 0;
            if(this->soundElementGenerationHasStarted)
                 nextBeatTime = this->lastBeatTime + this->clickConfiguration->getFramesPerBeat();
            
            //add sounds
            for(int32_t i = 0; i<this->y; i++)
            {
                int64_t nextTime = nextBeatTime + i * this->clickConfiguration->getFramesPerBeat() / this->y;
                
                //decide which SoundElement has to be used
                if(x == 0)
                {
                    if(this->xSoundElement != NULL)
                    {
                        SoundElement* se = this->xSoundElement->cloneAndSetTime(nextTime);
                        se->setPlaybackCallback( boost::bind( &ClickGenerator_XoverY::playbackCallbackX, &(*this), x+1, _1, _2) );
                        this->soundElementList.push_back(se);
                    }
                }
                else
                {
                    if(this->ySoundElement != NULL)
                    {
                        SoundElement* se = this->ySoundElement->cloneAndSetTime(nextTime);
                        se->setPlaybackCallback( boost::bind( &ClickGenerator_XoverY::playbackCallbackX, &(*this), x+1, _1, _2) );
                        this->soundElementList.push_back(se);
                    }
                }
                
                //increment x
                x = (x + 1) % this->x;
            }
            
            //increment lastBeatTime
            this->lastBeatTime = nextBeatTime;
            
            //indicate that SoundElement generation has started
            this->soundElementGenerationHasStarted = true;
        }
    }
    
    void ClickGenerator_XoverY::setClickConfiguration(ClickConfiguration* cc)
    {
        this->clickConfiguration = cc;
        this->lastBeatTime = cc->getReferenceTime();
        this->cleanSoundElements();
    }
    
    ClickConfiguration* ClickGenerator_XoverY::getClickConfiguration()
    {
        return this->clickConfiguration;
    }
    
    std::list<SoundElement*>* ClickGenerator_XoverY::getSoundElementList(int64_t time)
    {
        //generate new elements for the future in soundElementList
        this->generateSoundElements( time );
        
        //return list
        return &this->soundElementList;
    }
    
    void ClickGenerator_XoverY::cleanSoundElements()
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
    
    void ClickGenerator_XoverY::playbackCallbackX(int32_t xCount, double timeStamp, boost::function<double(void)> timeFuncPointer )
    {
        xCountCallbackStruct* s = new xCountCallbackStruct;
        s->xCount = xCount;
        s->timeStamp = timeStamp;
        s->timeFuncPointer = timeFuncPointer;
        this->xCountCallbackStructList.push_back(s);
    }
    
    void ClickGenerator_XoverY::xCountCallbackWorkerFunction()
    {
        //run until object should be deleted
        while( !this->xCountCallbackThreadShouldStop )
        {
            //sleep
            boost::this_thread::sleep( boost::posix_time::milliseconds(20) );
            
            if(!this->xCountCallbackStructList.empty() &&
               this->xCountCallbackFunction != NULL)
            {
                //delete elements in beatCountCallbackStructList
                for(std::list<xCountCallbackStruct*>::iterator it = this->xCountCallbackStructList.begin(); it!=this->xCountCallbackStructList.end(); /*nothing*/)
                {
                    if( (*it)->timeStamp <= (*it)->timeFuncPointer() )
                    {
                        //remove element from list
                        xCountCallbackStruct* s = *it;
                        it = this->xCountCallbackStructList.erase(it);
                        
                        //call callback function
                        this->xCountCallbackFunction(s->xCount);
                        
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
