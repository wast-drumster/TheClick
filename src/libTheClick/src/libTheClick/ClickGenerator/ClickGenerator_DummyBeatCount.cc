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

#include "libTheClick/ClickGenerator/ClickGenerator_DummyBeatCount.h"
#include "libTheClick/definitions.h"
#include "libTheClick/SoundBase.h"
#include "libTheClick/Sound/Sound_Mono.h"

#include "boost/bind.hpp"

#include <stdexcept>

//DEBUG
//#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    ClickGenerator_DummyBeatCount::ClickGenerator_DummyBeatCount()
    {
        //initialize
        this->clickConfiguration = NULL;
        this->beatCountCallbackFunction = NULL;
 
        //create beatCallBackThread
        this->beatCountCallbackThreadShouldStop = false;
        this->beatCountCallbackThread = new boost::thread( boost::bind( &ClickGenerator_DummyBeatCount::beatCountCallbackWorkerFunction, &(*this) ) );
        
        //reset
        this->reset();
    }
    
    ClickGenerator_DummyBeatCount::~ClickGenerator_DummyBeatCount()
    {
        //stop beatCountCallbackThread
        this->beatCountCallbackThreadShouldStop = true;
        this->beatCountCallbackThread->join();
        delete this->beatCountCallbackThread;
        
        //delete elements in beatCountCallbackStructList
        for(std::list<beatCountCallbackStruct*>::iterator it = this->beatCountCallbackStructList.begin(); it!=this->beatCountCallbackStructList.end(); /*nothing*/)
        {
            delete *it;
            it = this->beatCountCallbackStructList.erase(it);
            
            //end condition
            if(it == this->beatCountCallbackStructList.end())
                break;
        }
    }
    
    //*****************************
    //********** METHODS **********
    //*****************************
    void ClickGenerator_DummyBeatCount::reset()
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
           
    void ClickGenerator_DummyBeatCount::generateSoundElements(int64_t endTime)
    {
        //calculate amount of beats
        int32_t beats = 0;
        if(this->soundElementGenerationHasStarted)
            beats = this->clickConfiguration->getReferenceBeatCount() + 1 + (this->lastBeatTime - this->clickConfiguration->getReferenceTime()) / this->clickConfiguration->getFramesPerBeat();

        //debug
//        std::cout << "thread_id: " << boost::this_thread::get_id() << "   new beats: " << beats << std::endl;
        
        while(this->lastBeatTime < endTime)
        {
            //calculate nextBeatTime
            int64_t nextBeatTime = 0;
            if(this->soundElementGenerationHasStarted)
                 nextBeatTime = this->lastBeatTime + this->clickConfiguration->getFramesPerBeat();
            
            //debug
//            std::cout << std::setprecision(15) << "beats: " << beats << "   nextBeatTime: " << (double)nextBeatTime/SAMPLE_RATE << std::endl;
            
            //add sound for beat (main division)
            SoundElement* seBeat = new SoundElement(-1, -1, new Sound_Mono(1), 1.0f);
            seBeat->time = nextBeatTime;
            seBeat->setPlaybackCallback( boost::bind( &ClickGenerator_DummyBeatCount::playbackCallbackBeat, &(*this), beats+1, _1, _2) );
            this->soundElementList.push_back(seBeat);
            
            //debug
//            std::cout << "add call back for: " << beats << std::endl;
            
            //increment lastBeatTime
            this->lastBeatTime = nextBeatTime;
            
            //increment beats
            beats++;
            
            //indicate that SoundElement generation has started
            this->soundElementGenerationHasStarted = true;
        }
    }
    
    void ClickGenerator_DummyBeatCount::setClickConfiguration(ClickConfiguration* cc)
    {
        this->clickConfiguration = cc;
        this->lastBeatTime = cc->getReferenceTime();
        this->cleanSoundElements();
    }
    
    ClickConfiguration* ClickGenerator_DummyBeatCount::getClickConfiguration()
    {
        return this->clickConfiguration;
    }
    
    std::list<SoundElement*>* ClickGenerator_DummyBeatCount::getSoundElementList(int64_t time)
    {
        //generate new elements for the future in soundElementList
        this->generateSoundElements( time );
        
        //remove old elements in soundElementList
        //this->cleanSoundElementList();
        
        //return list
        return &this->soundElementList;
    }
    
    void ClickGenerator_DummyBeatCount::cleanSoundElements()
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
        
    void ClickGenerator_DummyBeatCount::playbackCallbackBeat(int32_t beatCount, double timeStamp, boost::function<double(void)> timeFuncPointer )
    {
        beatCountCallbackStruct* s = new beatCountCallbackStruct;
        s->beatCount = beatCount;
        s->timeStamp = timeStamp;
        s->timeFuncPointer = timeFuncPointer;
        this->beatCountCallbackStructList.push_back(s);
    }
    
    void ClickGenerator_DummyBeatCount::beatCountCallbackWorkerFunction()
    {
        //run unteil object should be deleted
        while( !this->beatCountCallbackThreadShouldStop )
        {
            //sleep
            boost::this_thread::sleep( boost::posix_time::milliseconds(20) );
            
            if(!this->beatCountCallbackStructList.empty() &&
               this->beatCountCallbackFunction != NULL)
            {
                //delete elements in beatCountCallbackStructList
                for(std::list<beatCountCallbackStruct*>::iterator it = this->beatCountCallbackStructList.begin(); it!=this->beatCountCallbackStructList.end(); /*nothing*/)
                {
                    if( (*it)->timeStamp <= (*it)->timeFuncPointer() )
                    {
                        //remove element from list
                        beatCountCallbackStruct* s = *it;
                        it = this->beatCountCallbackStructList.erase(it);
                        
                        //call callback function
                        this->beatCountCallbackFunction(s->beatCount);
                        
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
