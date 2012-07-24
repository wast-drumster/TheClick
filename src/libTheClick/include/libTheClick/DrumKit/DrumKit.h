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

#ifndef _DRUMKIT_HEADER_
#define _DRUMKIT_HEADER_

#include "libTheClick/DrumKit/Instrument.h"
#include "libTheClick/Sound/SoundElement.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/util/PlatformUtils.hpp>


#include "libTheClick/types.h"
#include <string>
#include <list>

namespace libTheClick
{
        
    class DrumKit
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            DrumKit(std::string* path);
            virtual ~DrumKit();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            //file information
            std::string* path;
        
            //metainfo
            std::string* author;
            std::string* name;
            std::string* info;
        
            //instruments
            std::list<Instrument*> instrumentList;
            
        //********** METHODS **********
        public:
            SoundElement* cloneSoundElementWithVolume(int32_t instrumentID, float vol);
            void loadAllSoundFiles();
        
        protected: 
            
        private:
            //parse XML DrumKit document
            void loadDrumKitXMLFile();
            void parseDrumKitDocument(XERCES_CPP_NAMESPACE::XercesDOMParser* parser);
            void parseRootElement(XERCES_CPP_NAMESPACE::DOMElement* domElement);
            
            void parseDrumKit(XERCES_CPP_NAMESPACE::DOMElement* domElement);
            void parseDrumKitAuthor(XERCES_CPP_NAMESPACE::DOMNode* domNode);
            void parseDrumKitName(XERCES_CPP_NAMESPACE::DOMNode* domNode);
            void parseDrumKitInfo(XERCES_CPP_NAMESPACE::DOMNode* domNode);
        
            void parseDrumKitInstrumentList(XERCES_CPP_NAMESPACE::DOMNode* domNode);
        
        
        
            
            
    }; //class DrumKit
        
} //namespace libTheClick

#endif // _DRUMKIT_HEADER_
