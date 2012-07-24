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

#ifndef _CLICKCONFIGURATION_HEADER_
#define _CLICKCONFIGURATION_HEADER_

#include "libTheClick/SoundBase.h"
#include "libTheClick/definitions.h"
#include "libTheClick/types.h"

namespace libTheClick
{
        
    class ClickConfiguration
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            ClickConfiguration(SoundBase* sb);
            virtual ~ClickConfiguration();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            int32_t beatsPerMinute;
            int64_t referenceTime;
            int64_t readTime;
            int64_t referenceBeatCount;
        
            SoundBase* soundBase;
            
        //********** METHODS **********
        public:
            void                  reset();
        
            inline int32_t        getBeatsPerMinute() const {return this->beatsPerMinute;}
            void                  setBeatsPerMinute(int32_t bpm);
            inline int32_t        getFramesPerBeat() const {return (SAMPLE_RATE * ((int64_t)60)) / this->beatsPerMinute;}
            
            inline int64_t        getReferenceTime() const {return this->referenceTime;}
            void                  setReferenceTime(int64_t ref);
            inline int64_t        getReferenceBeatCount() const {return this->referenceBeatCount;}
        
            inline int64_t        getReadTime() const {return this->readTime;}
            inline void                  incrementReadTime() {this->readTime++;}
        
            inline SoundBase*     getSoundBase() const {return this->soundBase;}
            inline void           setSoundBase(SoundBase* sb) {this->soundBase = sb;}
        
        protected: 
            
        private:
            
            
    }; //class ClickConfiguration
        
} //namespace libTheClick

#endif // _CLICKCONFIGURATION_HEADER_
