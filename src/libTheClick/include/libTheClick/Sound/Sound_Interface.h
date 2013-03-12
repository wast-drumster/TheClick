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

#ifndef _Sound_INTERFACE_HEADER_
#define _Sound_INTERFACE_HEADER_

#include "libTheClick/types.h"
#include <string>


namespace libTheClick
{
        
    class Sound_Interface
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            explicit Sound_Interface();
            virtual ~Sound_Interface() {}
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            
        //********** METHODS **********
        public:
            virtual float*           getSoundBufferMono() = 0;
            virtual float*           getSoundBufferLeft() = 0;
            virtual float*           getSoundBufferRight() = 0;
            virtual const int64_t    getLength() const = 0;
            virtual Sound_Interface* clone() = 0;
            virtual Sound_Interface* cloneWithVolume(float vol) = 0;
        
            //Factory
            static Sound_Interface* loadSoundFromFile(std::string& path);
            static Sound_Interface* loadSoundFromFile(const char *path);
        
        protected: 
            
        private:
            
            
    }; //class Sound_Interface
        
} //namespace libTheClick

#endif // _Sound_INTERFACE_HEADER_
