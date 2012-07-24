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

#include "libTheClick/helper/Xerces/DOMTreeErrorHandler.h"
#include "libTheClick/definitions.h"
#include "libTheClick/helper/Xerces/StrX.h"

#include <xercesc/sax/SAXParseException.hpp>

//#include <stdexcept>

//DEBUG
#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    DOMTreeErrorHandler::DOMTreeErrorHandler()
    {
        //initialize
        this->errorsOccurred = false;
    }
        
    DOMTreeErrorHandler::~DOMTreeErrorHandler()
    {
    }
        
    //*****************************
    //********** METHODS **********
    //*****************************
    const bool& DOMTreeErrorHandler::getErrorsOccurred() const
    {
        return this->errorsOccurred;
    }
    
    void DOMTreeErrorHandler::warning(const XERCES_CPP_NAMESPACE::SAXParseException& toCatch)
    {
        //
        // Ignore all warnings.
        //
    }
    
    void DOMTreeErrorHandler::error(const XERCES_CPP_NAMESPACE::SAXParseException& toCatch)
    {
        this->errorsOccurred= true;
        
        std::cerr << "Error at file \"" << StrX(toCatch.getSystemId()).CString()
        << "\", line " << toCatch.getLineNumber()
        << ", column " << toCatch.getColumnNumber()
        << "\n   Message: " << StrX(toCatch.getMessage()).CString() << std::endl;
    }
    
    void DOMTreeErrorHandler::fatalError(const XERCES_CPP_NAMESPACE::SAXParseException& toCatch)
    {
        this->errorsOccurred= true;
        
        std::cerr << "Fatal Error at file \"" << StrX(toCatch.getSystemId()).CString()
        << "\", line " << toCatch.getLineNumber()
        << ", column " << toCatch.getColumnNumber()
        << "\n   Message: " << StrX(toCatch.getMessage()).CString() << std::endl;
    }
    
    void DOMTreeErrorHandler::resetErrors()
    {
        this->errorsOccurred= false;
    }

    

} //namespace libTheClick
