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

#ifndef _SOUND_MONO_HEADER_
#define _SOUND_MONO_HEADER_

#include "libTheClick/Sound/Sound_Interface.h"

#include "libTheClick/types.h"
#include <string>

namespace libTheClick
{
        
    class Sound_Mono : public Sound_Interface
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            explicit Sound_Mono(std::string& path); //load from file
            explicit Sound_Mono(const char *path); //load from file
            explicit Sound_Mono(int64_t length);   //generate empty sound buffer
            explicit Sound_Mono(const Sound_Mono& rhs); //copy constructor
            virtual ~Sound_Mono();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            float*  soundBuffer;
            int64_t length;
            
        //********** METHODS **********
        public:
            //implement Sound_Interface
            virtual inline const int64_t getLength() const {return this->length;}
            virtual inline float* getSoundBufferMono() {return this->soundBuffer;}
            virtual inline float* getSoundBufferLeft() {return this->soundBuffer;}
            virtual inline float* getSoundBufferRight() {return this->soundBuffer;}
            virtual inline Sound_Interface* clone() {return new Sound_Mono( *this );}
            virtual Sound_Interface* cloneWithVolume(float vol);
        
            //own methods
            //nothing up to now
        
        protected: 
            
        private:
            void normalize();
            
    }; //class Sound_Mono
        
} //namespace libTheClick

#endif // _SOUND_MONO_HEADER_
