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

#include "libTheClick/SoundBase.h"
#include "libTheClick/definitions.h"

#include "libTheClick/Sound/SoundElement.h"
#include <stdexcept>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    SoundBase::SoundBase()
    {
    }
    
    SoundBase::~SoundBase()
    {
        for(std::map<drumkit_id,DrumKit*>::iterator it = this->drumKitMap.begin(); it != this->drumKitMap.end(); it++)
        {
            delete it->second;
        }
    }
        
    //*****************************
    //********** METHODS **********
    //*****************************    
    SoundElement* SoundBase::getSoundElement(drumkit_id drumKitID, int32_t soundIndex, float volume)
    {
        //get drum kit
        DrumKit* dk = this->drumKitMap[drumKitID];
        
        //set DrumKitID
        SoundElement* se = dk->cloneSoundElementWithVolume(soundIndex, volume);
        if(se != NULL)
           se->drumKitID = drumKitID;
        
        //return sound from drum kit
        return  se;
    }
    
    drumkit_id SoundBase::loadDrumKit(const char* const path)
    {
        std::string localPath(path);
        return this->loadDrumKit( &localPath );
    }
    
    drumkit_id SoundBase::loadDrumKit(std::string* path)
    {
        //create new ID
        drumkit_id newID = this->drumKitMap.size();
        
        //load drum kit
        this->drumKitMap[newID] = new DrumKit(path);
        
        //return ID
        return newID;
    }
    
    void SoundBase::loadAllSoundFiles()
    {
        for(std::map<drumkit_id,DrumKit*>::iterator it = this->drumKitMap.begin(); it != this->drumKitMap.end(); it++)
        {
            it->second->loadAllSoundFiles();
        }
    }
    
} //namespace libTheClick
