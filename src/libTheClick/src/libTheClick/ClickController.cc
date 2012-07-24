/*
** Copyright (C) 2012 Sebastian Roeglinger <wast-drumster@gmail.com>
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

#include "libTheClick/ClickController.h"
#include "libTheClick/definitions.h"
#include "libTheClick/Sound/SoundElement.h"

#include "portaudio.h"
#include "boost/bind.hpp"

#include <stdexcept>

//debug
#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    ClickController::ClickController()
    {
        //initialize attributes
        SoundBase* sb = new SoundBase();
        //sb->loadDrumKit( "/Users/wast/Library/Application Support/Hydrogen/drumkits/UltraAcousticKit" );
        //sb->loadDrumKit( "/Users/wast/Library/Application Support/Hydrogen/drumkits/The Black Pearl 1.0" );
        //sb->loadDrumKit( "/Users/wast/Library/Application Support/Hydrogen/drumkits/RedRokkit" );
        //sb->loadDrumKit( "/Users/wast/Library/Application Support/Hydrogen/drumkits/GSCW-1" );
        //sb->loadDrumKit( "/Users/wast/Library/Application Support/Hydrogen/drumkits/GSCW-2" );
        sb->loadDrumKit( "/Users/wast/Library/Application Support/Hydrogen/drumkits/BigMono" );
        //sb->loadDrumKit( "/Users/wast/Library/Application Support/Hydrogen/drumkits/Millo_MultiLayered3" );
        //sb->loadAllSoundFiles();
        this->clickConfiguration = new ClickConfiguration( sb );
        this->clickGenAddCounter = 0;
        
        //initialize Portaudio
        PaError err;

        err = Pa_Initialize();
        if( err != paNoError ) throw std::logic_error("Portaudio initialization error");
        
        err = Pa_OpenDefaultStream(&this->outPaStream,
                                   0,          /* no input channels */
                                   2,          /* stereo output */
                                   paFloat32,  /* 32 bit floating point output */
                                   SAMPLE_RATE,
                                   SAMPLE_RATE/2 /*paFramesPerBufferUnspecified*/,        /* frames per buffer, i.e. the number
                                                of sample frames that PortAudio will
                                                request from the callback. Many apps
                                                may want to use
                                                paFramesPerBufferUnspecified, which
                                                tells PortAudio to pick the best,
                                                possibly changing, buffer size.*/
                                   ClickController::paCallback, /* this is your callback function */
                                   this ); /*This is a pointer that will be passed to
                                          your callback*/
        if( err != paNoError ) throw std::logic_error("Portaudio could not open output stream.");        
    }

    ClickController::~ClickController()
    {
        //delete all elements in clickGeneratorVector
        for(std::map<clickgen_id,ClickGeneratorElement*>::iterator it = this->clickGeneratorMap.begin(); it != this->clickGeneratorMap.end(); it++)
        {
            delete it->second;
            this->clickGeneratorMap.erase(it);
        }
                
        //close Portaudio
        PaError err;
        if(this->outPaStream != NULL)
        {
            //err = Pa_AbortStream(this->outPaStream);
            err = Pa_CloseStream(this->outPaStream);
            if( err != paNoError ) throw std::logic_error("Portaudio could not be aborted.");
        }
        
        err = Pa_Terminate();
        if( err != paNoError ) throw std::logic_error("Portaudio could not be closed.");        
    }
    
    //*****************************
    //********** METHODS **********
    //*****************************
    clickgen_id ClickController::addClickGenerator(ClickGenerator_Interface* cg, float vol)
    {
        //TBD: Check that vol >=0
        
        //generate new clickgen_id
        clickgen_id ret = this->clickGenAddCounter;
        this->clickGenAddCounter++;
        
        //set ClickConfiguration in ClickGenerator
        //This must be done before the ClickGenerator is added to the clickGeneratorMap because at this call, all missing click are generated which might take some processing time.
        cg->setClickConfiguration(this->clickConfiguration);
        
        //add ClickGenerator to clickGeneratorVector
        this->clickGeneratorMap[ret] = new ClickGeneratorElement(cg, vol);
        
        //debug
        //std::cout << "addClickGenerator vol: " << vol << std::endl;
        
        //return id
        return ret;
    }
    
    void ClickController::setVolumeforClickGenerator(clickgen_id id, float vol)
    {
        //TBD: Check that vol >=0
        
        //debug
        //std::cout << "setVolumeforClickGenerator vol: " << vol << std::endl;
        
        this->clickGeneratorMap[id]->vol = vol;
    }
    
    void ClickController::removeClickGenerator(clickgen_id id)
    {
        this->clickGeneratorMap.erase(id);
    }
    
    void ClickController::start()
    {
        //debug
        //std::cout << "start" << std::endl;
        
        //start portaudio
        if( Pa_IsStreamStopped(this->outPaStream) == 1)  //1: stopped, 0: running
        {
            PaError err = Pa_StartStream( this->outPaStream );
            if( err != paNoError ) throw std::logic_error("Portaudio could not be started.");
        }
    }
    
    void ClickController::stop()
    {
        //debug
        //std::cout << "stop" << std::endl;
        
        //stop portaudio
        if( Pa_IsStreamStopped(this->outPaStream) == 0)  //1: stopped, 0: running
        {
            PaError err = Pa_StopStream( this->outPaStream );
            if( err != paNoError ) throw std::logic_error("Portaudio could not be stoped.");
        }
    }
    
    void ClickController::reset()
    {
        //debug
        //std::cout << "reset" << std::endl;
        
        //reset
        this->stop();
        this->clickConfiguration->reset();
        
        for(std::map<clickgen_id,ClickGeneratorElement*>::iterator it = this->clickGeneratorMap.begin(); it != this->clickGeneratorMap.end(); it++)
        {
            (*it).second->cg->reset();
        }
        
        //clean soundElementList
        for(std::list<SoundElement*>::iterator it=this->soundElementList.begin(); it != this->soundElementList.end(); it++)
        {
            delete *it;
            this->soundElementList.erase(it);
        }
        
    }
    
    int ClickController::paCallback(const void *inputBuffer, void *outputBuffer,
                                    unsigned long framesPerBuffer,
                                    const PaStreamCallbackTimeInfo* timeInfo,
                                    PaStreamCallbackFlags statusFlags,
                                    void *userData )
    {
        //debug
        //std::cout << "paCallback" << std::endl;
        //std::cout << "paCallback; outputBufferDacTime: " << std::setprecision(15) << timeInfo->outputBufferDacTime << std::endl;
        
        //cast data passed through stream to useable structure
        ClickController* cc = (ClickController*)userData;
        float* out = (float*)outputBuffer;
        (void) inputBuffer; // prevent unused variable warning

        //move SoundElements from ClickGenerators to own SoundElementVector
        for(std::map<clickgen_id,ClickGeneratorElement*>::iterator it1 = cc->clickGeneratorMap.begin(); it1 != cc->clickGeneratorMap.end(); it1++)
        {
            //update and get ClickGenerator's ElementList
            std::list<SoundElement*>* sel = (*it1).second->cg->getSoundElementList(cc->clickConfiguration->getReadTime() + framesPerBuffer);
            
            //move sound elements to own list if they have to be played
            for (std::list<SoundElement*>::iterator it2=sel->begin(); it2 != sel->end(); /*nothing*/)
            {
                if( (*it2)->time <= cc->clickConfiguration->getReadTime() + framesPerBuffer )
                {
                    //modify volume in SoundElement
                    (*it2)->multiplayVolumeWith( (*it1).second->vol );

                    //call SoundElement's callback function
                    (*it2)->callPlaybackCallback(
                        timeInfo->outputBufferDacTime + (double)((*it2)->time - cc->clickConfiguration->getReadTime()) / (double)SAMPLE_RATE,
                        //&timeInfo->currentTime
                        boost::bind( &Pa_GetStreamTime, cc->outPaStream )
                    );
                    
                    //move SoundElement
                    cc->soundElementList.push_back( *it2 );
                    it2 = sel->erase( it2 );
                    
                    //end criterion
                    if(it2 == sel->end()) break;
                }
                else
                {
                    it2++;
                }
            }
            
        }
        
        //playback SoundElements
        for(int32_t i=0; i < framesPerBuffer*2; i=i+2 )
        {
            //pre-set output values
            out[i] = 0.0f;
            out[i+1] = 0.0f;
            
            //add sound frames to output
            for(std::list<SoundElement*>::iterator it=cc->soundElementList.begin(); it != cc->soundElementList.end(); it++)
            {
                if((*it)->time <= cc->clickConfiguration->getReadTime() &&
                   (*it)->time + (*it)->getSound()->getLength() > cc->clickConfiguration->getReadTime())
                {
                    out[i]   += (*it)->getVolume() * (*it)->getSound()->getSoundBufferLeft()[cc->clickConfiguration->getReadTime() - (*it)->time];
                    out[i+1] += (*it)->getVolume() * (*it)->getSound()->getSoundBufferRight()[cc->clickConfiguration->getReadTime() - (*it)->time];
                }
            }
            
            //increment read time counter
            cc->clickConfiguration->incrementReadTime();
        }
        
        //delete SoundElements which are to old
        for(std::list<SoundElement*>::iterator it=cc->soundElementList.begin(); it != cc->soundElementList.end(); /*nothing*/)
        {
            //calculate time between internalTime and end-frame of sound element
            int64_t timeGap = (*it)->time + (*it)->getSound()->getLength() - cc->clickConfiguration->getReadTime();
            
            if( timeGap < 0 )
            {
                //erase element from list
                delete *it;
                it = cc->soundElementList.erase(it);

                //end criterion
                if(it == cc->soundElementList.end()) break;
            }
            else
            {
                it++;
            }
        }
        
        //return
        return 0;
    }
    
    void ClickController::setBeatsPerMinute(int32_t bpm)
    {
        
        //reset reference time and reference beat count in configuration
        this->clickConfiguration->setReferenceTime(this->clickConfiguration->getReadTime() /*+ SAMPLE_RATE*/);
        
        //reset BPMs in Configuration
        //It is very important that the referenceTime is set BEFORE the new BPM value!
        this->clickConfiguration->setBeatsPerMinute(bpm);
        
        //reset all ClickGenerators
        for(std::map<clickgen_id,ClickGeneratorElement*>::iterator it = this->clickGeneratorMap.begin(); it != this->clickGeneratorMap.end(); it++)
        {
            (*it).second->cg->cleanSoundElements();
        }
        
        //cli output
        //std::cout << "BPM: " << bpm << std::endl;
        
    }
    
    SoundBase* ClickController::getSoundBase() const
    {
        return this->clickConfiguration->getSoundBase();
    }
    
} //namespace libTheClick
