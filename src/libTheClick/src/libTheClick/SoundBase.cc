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
    SoundElement* SoundBase::getSoundElement(drumkit_id drumKitID, instrument_id instrumentID, float volume)
    {
        SoundElement* ret = NULL;
        
        //get drum kit
        DrumKit* dk = this->drumKitMap[drumKitID];
        
        //set DrumKitID
        if(dk != NULL)
        {
            ret = dk->cloneSoundElementWithVolume(instrumentID, volume);
            if(ret != NULL)
               ret->drumKitID = drumKitID;
        }
        
        //return sound from drum kit
        return ret;
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
    
    std::list<SoundInformation>* SoundBase::getListOfAllSoundInformations() const
    {
        std::list<SoundInformation>* ret = new std::list<SoundInformation>();
        
        //walk through all drum kits
        for(std::map<drumkit_id,DrumKit*>::const_iterator it1 = this->drumKitMap.begin(); it1 != this->drumKitMap.end(); it1++)
        {
            std::list<SoundInformation>* sil = (*it1).second->getListOfAllSoundInformations();
            
            //copy all SoundINformation structs
            for(std::list<SoundInformation>::const_iterator it2 = sil->begin(); it2 != sil->end(); it2++)
            {
                SoundInformation si = (*it2);
                si.drumkitID = (*it1).first;
                ret->push_back(si);
            }
            
            delete sil;
        }
        
        //return
        return ret;
    }
    
    std::string SoundBase::getNameOfDrumKit(drumkit_id drumkitID)
    {
        DrumKit* dk = this->drumKitMap[drumkitID];
        return dk->getDrumKitName();
    }
    
    std::string SoundBase::getNameOfInstrument(drumkit_id drumkitID, instrument_id instrumentID)
    {
        DrumKit* dk = this->drumKitMap[drumkitID];
        return dk->getInstrumentName(instrumentID);
    }
    
    drumkit_id SoundBase::getDrumKitID(std::string name)
    {
        for(std::map<drumkit_id,DrumKit*>::iterator it = this->drumKitMap.begin(); it != this->drumKitMap.end(); it++)    
        {
            if( (*it).second->getDrumKitName() == name )
                return (*it).first;
        }
        
        throw std::logic_error("Drumkit not found.");
        return 0; //avoid warning
    }
    
    instrument_id SoundBase::getInstrumentID(drumkit_id drumkitID, std::string name)
    {
        DrumKit* dk = this->drumKitMap[drumkitID];
        
        return dk->getInstrumentID(name);
    }
    
    instrument_id SoundBase::getInstrumentID(std::string drumkitStr, std::string instrumentStr)
    {
        drumkit_id drumkitID = this->getDrumKitID(drumkitStr);
        return this->getInstrumentID(drumkitID, instrumentStr);
    }
    
} //namespace libTheClick
