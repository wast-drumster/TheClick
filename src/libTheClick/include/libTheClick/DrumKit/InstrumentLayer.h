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

#ifndef _INSTRUMENT_LAYER_HEADER_
#define _INSTRUMENT_LAYER_HEADER_

#include "libTheClick/Sound/SoundElement.h"

#include <xercesc/dom/DOM.hpp>
//#include <xercesc/parsers/XercesDOMParser.hpp>
//#include <xercesc/util/OutOfMemoryException.hpp>
//#include <xercesc/util/PlatformUtils.hpp>


#include "libTheClick/types.h"
#include <string>

namespace libTheClick
{
        
    class InstrumentLayer
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            InstrumentLayer(std::string* fileName, float min, float max, std::string* path);
            InstrumentLayer(XERCES_CPP_NAMESPACE::DOMNode* domNode, std::string* path);
            virtual ~InstrumentLayer();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            //file
            std::string* path;
            SoundElement* soundElement;
        
            //instrument
            std::string* fileName;
            float min;
            float max;
        
            
        //********** METHODS **********
        public:
            SoundElement* cloneSoundElementWithVolume(float vol);
            const float& getMin() const;
            const float& getMax() const;
            void loadSoundFile();
            bool soundElementIsUnique();
            void freeMemory();
        
        protected: 
            
        private:
            
            
    }; //class InstrumentLayer
        
} //namespace libTheClick

#endif // _INSTRUMENT_LAYER_HEADER_
