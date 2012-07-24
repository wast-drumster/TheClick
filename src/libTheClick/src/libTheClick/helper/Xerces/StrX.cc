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

#include "libTheClick/helper/Xerces/StrX.h"
#include "libTheClick/definitions.h"

//#include <stdexcept>

//DEBUG
//#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    StrX::StrX(const XMLCh* const toTranscode) : toTranscode(toTranscode)
    {
        this->toTranscodeCString = NULL;
        this->toTranscodeStdString = NULL;
    }
        
    StrX::~StrX()
    {
        if(this->toTranscodeCString != NULL)
            XERCES_CPP_NAMESPACE::XMLString::release(&this->toTranscodeCString);
        
        if(this->toTranscodeStdString != NULL)
            delete this->toTranscodeStdString;
    }

    //*****************************
    //********** METHODS **********
    //*****************************
    const char* StrX::CString()
    {
        //convert XMLCh to CSting
        if(this->toTranscodeCString == NULL)
            this->toTranscodeCString = XERCES_CPP_NAMESPACE::XMLString::transcode(this->toTranscode);
        
        //return CString
        return this->toTranscodeCString;
    }
    
    const std::string& StrX::StdString()
    {
        //convert XMLCh to CSting
        if(this->toTranscodeStdString == NULL)
            this->toTranscodeStdString = new std::string(this->CString());
        
        //return CString
        return *this->toTranscodeStdString;
    }

    bool StrX::isEqual(const char* cString)
    {
        return strcmp(this->CString(), cString) == 0;
    }

} //namespace libTheClick
