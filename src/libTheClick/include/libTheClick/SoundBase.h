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

#ifndef _SOUNDBASE_HEADER_
#define _SOUNDBASE_HEADER_

#include "libTheClick/DrumKit/DrumKit.h"
#include "libTheClick/types.h"
#include <map>

namespace libTheClick
{
        
    class SoundBase
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            SoundBase();
            virtual ~SoundBase();
            
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            std::map<drumkit_id, DrumKit*> drumKitMap;
            
        //********** METHODS **********
        public:
            SoundElement* getSoundElement(drumkit_id drumKitID, int32_t soundIndex, float volume);
            drumkit_id loadDrumKit(const char* const path);
            drumkit_id loadDrumKit(std::string* path);
            void loadAllSoundFiles();
        
        protected: 
            
        private:
            
            
    }; //class SoundBase
        
} //namespace libTheClick

#endif // _SOUNDBASE_HEADER_
