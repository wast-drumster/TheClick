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

#include "libTheClick/ClickConfiguration.h"
#include "libTheClick/definitions.h"

#include <stdexcept>


namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    ClickConfiguration::ClickConfiguration(SoundBase* sb)
    {
        //initialization
        this->beatsPerMinute = 60;
        this->soundBase = sb;
        
        //reset
        this->reset();
    }

    ClickConfiguration::~ClickConfiguration()
    {
        if(this->soundBase != NULL)
        {
            delete this->soundBase;
            this->soundBase = NULL;
        }
    }
    
    //*****************************
    //********** METHODS **********
    //*****************************
    void ClickConfiguration::setBeatsPerMinute(int32_t bpm)
    {
        //check if bpm is in correct range
        if(bpm <= 0)
            throw std::logic_error("BPM has to by greater than '0'.");
        
        //set attribute
        this->beatsPerMinute = bpm;
    }

    void ClickConfiguration::setReferenceTime(int64_t ref)
    {
        //check if ref is in correct range
        if(ref < 0)
            throw std::logic_error("Reference time has to be greater than or equal to '0'.");
        
        //calculate new time
        int64_t newReferenceTime = 0;
        if(this->readTime != 0)
            newReferenceTime = this->referenceTime + ((ref - this->referenceTime) / this->getFramesPerBeat() + 1) * this->getFramesPerBeat();
        
        //calulcate new referenceBeatCount
        int64_t newReferenceBeatCount = this->referenceBeatCount + (newReferenceTime - this->referenceTime) / this->getFramesPerBeat();
        
        //debug
//        std::cout << "old referenceTime: " <<  this->referenceTime << std::endl;
//        std::cout << "old referenceBeatCount: " <<  this->referenceBeatCount << std::endl;
//        std::cout << "new referenceTime: " <<  newReferenceTime << std::endl;
//        std::cout << "new referenceBeatCount: " <<  newReferenceBeatCount << std::endl;
        
        //set attributes
        this->referenceTime = newReferenceTime;
        this->referenceBeatCount = newReferenceBeatCount;
    }
    
    void ClickConfiguration::reset()
    {
        this->referenceTime = 0;
        this->referenceBeatCount = 0;
        this->readTime = 0;
    }
} //namespace libTheClick
