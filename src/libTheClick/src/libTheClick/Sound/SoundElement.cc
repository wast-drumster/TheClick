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

#include "libTheClick/Sound/SoundElement.h"
#include "libTheClick/definitions.h"

#include "libTheClick/Sound/Sound_Interface.h"

//#include <sndfile.h>
#include <stdexcept>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    SoundElement::SoundElement(drumkit_id drumKitID, instrument_id instrumentID, std::string& path, float volume)
    : drumKitID(drumKitID),
      instrumentID(instrumentID),
      playbackCallbackFunction(NULL),
      soundShrPtr( SoundInterfaceShrPtr( Sound_Interface::loadSoundFromFile(path) ) ),
      volume(volume)
    {
    }
    
    SoundElement::SoundElement(drumkit_id drumKitID, instrument_id instrumentID, const char *path, float volume)
    : drumKitID(drumKitID),
      instrumentID(instrumentID),
      playbackCallbackFunction(NULL),
      soundShrPtr( SoundInterfaceShrPtr( Sound_Interface::loadSoundFromFile(path) ) ),
      volume(volume)
    {
    }
    
    SoundElement::SoundElement(drumkit_id drumKitID, instrument_id instrumentID, Sound_Interface* sound, float volume)
    : drumKitID(drumKitID),
      instrumentID(instrumentID),
      playbackCallbackFunction(NULL),
      soundShrPtr(SoundInterfaceShrPtr(sound)),
      volume(volume)
    {
    }
    
    SoundElement::SoundElement(const SoundElement& se)
    : time(se.time),
      drumKitID(se.drumKitID),
      instrumentID(se.instrumentID),
      playbackCallbackFunction(NULL),
      soundShrPtr(se.soundShrPtr),
      volume(se.volume)
    {
    }
    
    SoundElement::~SoundElement()
    {
    }
        
    //*****************************
    //********** METHODS **********
    //*****************************
    SoundElement* SoundElement::clone()
    {
        SoundElement* ret = NULL;
        
        if(this != NULL)
            ret = new SoundElement( *this );
        
        return ret;
    }
    
    SoundElement* SoundElement::cloneAndSetTime(int64_t time)
    {
        SoundElement* ret = this->clone();
        ret->time = time;
        return ret;
    }
    
    void SoundElement::callPlaybackCallback(double timeStamp, boost::function<double(void)> timeFuncPointer)
    {
        //debug
//        std::cout << "debug; timeFuncPointer:" << timeFuncPointer() << std::endl;
        
        //work
        if(this->playbackCallbackFunction != NULL)
            this->playbackCallbackFunction(timeStamp, timeFuncPointer);
    }
    
} //namespace libTheClick
