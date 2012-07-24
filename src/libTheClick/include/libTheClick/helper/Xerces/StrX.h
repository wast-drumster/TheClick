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

#ifndef _XERCESSTRX_HEADER_
#define _XERCESSTRX_HEADER_

#include <xercesc/util/XMLString.hpp>

#include "libTheClick/types.h"
#include <string>

namespace libTheClick
{
        
    class StrX
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            StrX(const XMLCh* const toTranscode);
            virtual ~StrX();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            const XMLCh* const toTranscode;
            
            char* toTranscodeCString;
            std::string* toTranscodeStdString;
            
        //********** METHODS **********
        public:
            const char* CString();
            const std::string& StdString();
        
            bool isEqual(const char* cString);
        
        protected: 
            
        private:
            
            
    }; //class StrX
        
} //namespace libTheClick

#endif // _XERCESSTRX_HEADER_
