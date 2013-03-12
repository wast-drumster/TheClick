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

#ifndef _SOUND_STEREO_HEADER_
#define _SOUND_STEREO_HEADER_

#include "libTheClick/Sound/Sound_Interface.h"

#include "libTheClick/types.h"
#include <string>

namespace libTheClick
{
        
    class Sound_Stereo : public Sound_Interface
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            explicit Sound_Stereo(std::string& path); //load from file
            explicit Sound_Stereo(const char *path); //load from file
            explicit Sound_Stereo(int64_t length);   //generate empty sound buffer
            explicit Sound_Stereo(const Sound_Stereo& rhs); //copy constructor
            virtual ~Sound_Stereo();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            float*  soundBufferLeft;
            float*  soundBufferRight;
            float*  soundBufferMono;
            int64_t length;
            
        //********** METHODS **********
        public:
            //implement Sound_Interface
            virtual inline const int64_t getLength() const {return this->length;}
            virtual float*  getSoundBufferMono();
            virtual inline float* getSoundBufferLeft() {return this->soundBufferLeft;}
            virtual inline float* getSoundBufferRight() {return this->soundBufferRight;}
            virtual inline Sound_Interface* clone() {return new Sound_Stereo( *this );}
            virtual Sound_Interface* cloneWithVolume(float vol);
        
            //own methods
            //nothing up to now
        
        protected: 
            
        private:
            void normalize();
            
    }; //class Sound
        
} //namespace libTheClick

#endif // _SOUND_STEREO_HEADER_
