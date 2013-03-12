/*
** Copyright (C) 2012-2013 Sebastian Roeglinger <wast.drumster@gmail.com>
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

#ifndef _DOMTREEERRORHANDLER_HEADER_
#define _DOMTREEERRORHANDLER_HEADER_

//#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>

#include "libTheClick/types.h"

namespace libTheClick
{
        
    class DOMTreeErrorHandler : public XERCES_CPP_NAMESPACE::ErrorHandler
    {
        //********** (DE/CON)STRUCTORS **********
        public:
            explicit DOMTreeErrorHandler();
            virtual ~DOMTreeErrorHandler();
        
        private:
            
        //********** ATTRIBUTES **********
        public:
            //! bool variable
            /*!
             * This variable indicates if a error occurred
             */
            bool errorsOccurred;
            
        protected: 
            
        private:
            
        //********** METHODS **********
        public:
            //Implementation of the error handler interface
            void warning(const XERCES_CPP_NAMESPACE::SAXParseException& toCatch);
            void error(const XERCES_CPP_NAMESPACE::SAXParseException& toCatch);
            void fatalError(const XERCES_CPP_NAMESPACE::SAXParseException& toCatch);
            void resetErrors();
            
            //class dependent
            const bool& getErrorsOccurred() const;
        
        protected: 
            
        private:
            
    }; //class DOMTreeErrorHandler
        
} //namespace libTheClick

#endif // _DOMTREEERRORHANDLER_HEADER_
