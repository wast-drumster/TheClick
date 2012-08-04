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

#ifndef _INSTRUMENT_HEADER_
#define _INSTRUMENT_HEADER_

#include "libTheClick/DrumKit/InstrumentLayer.h"
#include "libTheClick/types.h"

#include <xercesc/dom/DOM.hpp>
//#include <xercesc/parsers/XercesDOMParser.hpp>
//#include <xercesc/util/OutOfMemoryException.hpp>
//#include <xercesc/util/PlatformUtils.hpp>

#include "boost/thread.hpp"

#include <string>
#include <list>

namespace libTheClick
{
        
    class Instrument
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            Instrument(XERCES_CPP_NAMESPACE::DOMNode* domNode, std::string* path);
            virtual ~Instrument();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            //file
            std::string* path;
        
            //instrument
            int32_t id;
            std::string* name;
            std::list<InstrumentLayer*> instrumentLayerList;
        
            //garbage collector
            boost::thread* garbageCollectorThread;
            bool garbageCollectorThreadShouldStop;
            
        //********** METHODS **********
        public:
            SoundElement* cloneSoundElementWithVolume(float vol);
            const int32_t getId() const;
            void loadAllSoundFiles();
            std::string getName();
        
        protected: 
            
        private:
            bool checkWatherThereAreLayers(XERCES_CPP_NAMESPACE::DOMNode* domNode) const;
//            bool checkWatherThereAreExcludes(XERCES_CPP_NAMESPACE::DOMNode* domNode) const;
            void garbageCollectorWorkerFunction();
            
    }; //class Instrument
        
} //namespace libTheClick

#endif // _INSTRUMENT_HEADER_
