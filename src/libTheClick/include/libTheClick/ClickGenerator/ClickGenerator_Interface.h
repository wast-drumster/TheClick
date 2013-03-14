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

#ifndef _CLICKGENERATOR_INTERFACE_HEADER_
#define _CLICKGENERATOR_INTERFACE_HEADER_

#include "libTheClick/ClickConfiguration.h"
#include "libTheClick/Sound/SoundElement.h"

#include "libTheClick/types.h"
#include <list>
//#include <vector>

namespace libTheClick
{
        
    class ClickGenerator_Interface
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            //explicit ClickGenerator_Interface();
            virtual ~ClickGenerator_Interface() {}
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            
        //********** METHODS **********
        public: 
            virtual void   reset() = 0;
            virtual void   setClickConfiguration(ClickConfiguration* cc) = 0;
            virtual ClickConfiguration* getClickConfiguration() = 0;
            virtual std::list<SoundElement*>* getSoundElementList(int64_t time) = 0;
            virtual void   cleanSoundElements() = 0;
        
        protected: 
            
        private:
            
            
    }; //class ClickGenerator_Interface
        
} //namespace libTheClick

#endif // _CLICKGENERATOR_INTERFACE_HEADER_
