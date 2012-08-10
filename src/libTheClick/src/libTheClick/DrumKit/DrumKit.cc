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

#include "libTheClick/DrumKit/DrumKit.h"
#include "libTheClick/definitions.h"
#include "libTheClick/helper/Xerces/StrX.h"
#include "libTheClick/helper/Xerces/DOMTreeErrorHandler.h"

#include <stdexcept>

//DEBUG
#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    DrumKit::DrumKit(std::string* path)
    {
        //initialize attributes
        this->path = new std::string(*path);
        this->name = NULL;
        this->author = NULL;
        this->info = NULL;
        
        //load drumkit.xml
        this->loadDrumKitXMLFile();
    }
    
    DrumKit::~DrumKit()
    {
        //terminate XML stuff
        XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate();
        
        //delete attributes
        if(this->path != NULL)
            delete this->path;
        
        if(this->name != NULL)
            delete this->name;
        
        if(this->author != NULL)
            delete this->author;
        
        if(this->info != NULL)
            delete this->info;
        
        //delete elements in instrumentList
        for(std::list<Instrument*>::iterator it = this->instrumentList.begin(); it != this->instrumentList.end(); /*nothing*/)
        {
            it = this->instrumentList.erase(it);
            
            //end condition
            if(it == this->instrumentList.end()) break;
        }
    }
        
    //*****************************
    //********** METHODS **********
    //*****************************
    void DrumKit::loadDrumKitXMLFile()
    {
        //initialize XML stuff
        XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
        
        //create parser
        XERCES_CPP_NAMESPACE::XercesDOMParser* parser = new XERCES_CPP_NAMESPACE::XercesDOMParser();
        parser->setValidationScheme(XERCES_CPP_NAMESPACE::XercesDOMParser::Val_Auto);
        parser->setDoNamespaces(false);
        parser->setDoSchema(false);
        parser->setHandleMultipleImports(false);
        parser->setValidationSchemaFullChecking(true);
        //        parser->setCreateEntityReferenceNodes(gDoCreate);
        
        DOMTreeErrorHandler* errHandler = new DOMTreeErrorHandler();
        parser->setErrorHandler(errHandler);
        
        //parse document
        bool errorsOccured = false;
        try
        {
            std::string localPath( *this->path );
            localPath.append("/drumkit.xml");
            parser->parse( localPath.c_str() );
        }
        catch (const XERCES_CPP_NAMESPACE::OutOfMemoryException&)
        {
            std::cerr << "OutOfMemoryException" << std::endl;
            errorsOccured = true;
        }
        catch (const XERCES_CPP_NAMESPACE::XMLException& e)
        {
            std::cerr << "An error occurred during parsing\n   Message: "
            << StrX(e.getMessage()).CString() << std::endl;
            errorsOccured = true;
        }
        
        catch (const XERCES_CPP_NAMESPACE::DOMException& e)
        {
            const unsigned int maxChars = 2047;
            XMLCh errText[maxChars + 1];
            
            std::cerr << "\nDOM Error during parsing: '" << this->path << "'\n"
            << "DOMException code is:  " << e.code << std::endl;
            
            if (XERCES_CPP_NAMESPACE::DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
                std::cerr << "Message is: " << StrX(errText).CString() << std::endl;
            
            errorsOccured = true;
        }
        catch (...)
        {
            XERCES_STD_QUALIFIER cerr << "An error occurred during parsing\n " << XERCES_STD_QUALIFIER endl;
            errorsOccured = true;
        }
        
        
        // If the parse was successful, output the document data from the DOM tree
        if (!errorsOccured && !errHandler->getErrorsOccurred())
        {
            //std::cout << "test" << std::endl;
            
            try
            {
                this->parseDrumKitDocument(parser);
            }
            catch (const XERCES_CPP_NAMESPACE::OutOfMemoryException&)
            {
                std::cerr << "OutOfMemoryException" << std::endl;
                //                retval = 5;
            }
            catch (XERCES_CPP_NAMESPACE::XMLException& e)
            {
                StrX eMsg(e.getMessage());
                
                std::cerr << "An error occurred during creation of output transcoder. Msg is:"
                << std::endl
                << StrX(e.getMessage()).CString() << std::endl;
                //                retval = 4;
            }
        }
        
        //celan up
        delete parser;
        delete errHandler;
    }
    
    void DrumKit::parseDrumKitDocument(XERCES_CPP_NAMESPACE::XercesDOMParser* parser)
    {
        XERCES_CPP_NAMESPACE::DOMDocument* xmlDoc = parser->getDocument();
        
        XERCES_CPP_NAMESPACE::DOMElement* elementRoot = xmlDoc->getDocumentElement();
        
        //parse root element
        this->parseRootElement(elementRoot);
        
        //parse meat info of drum kit: name, author, and info
        this->parseDrumKit(elementRoot);
        
    }
    
    void DrumKit::parseRootElement(XERCES_CPP_NAMESPACE::DOMElement* domElement)
    {
        //std::cout << StrX(domElement->getTagName()).StdString() << std::endl;
        
        if( !StrX(domElement->getTagName()).isEqual("drumkit_info") )
            throw std::logic_error("wrong root element");
    }
    
    void DrumKit::parseDrumKit(XERCES_CPP_NAMESPACE::DOMElement* domElement)
    {
        XERCES_CPP_NAMESPACE::DOMNodeList* childNodeList = domElement->getChildNodes();
        
        //parse all child elements and use all relevant information
        for(int i = 0; i<childNodeList->getLength(); i++)
        {
            //get node
            XERCES_CPP_NAMESPACE::DOMNode* childNode = childNodeList->item(i);
            
            //work
            if(childNode->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
            {
                //debug
                //std::cout << StrX(childNode->getNodeName()).StdString() << std::endl;
                
                //work
                if( StrX(childNode->getNodeName()).isEqual("author") )
                {
                    this->parseDrumKitAuthor(childNode->getFirstChild());
                }
                else if( StrX(childNode->getNodeName()).isEqual("name") )
                {
                    this->parseDrumKitName(childNode->getFirstChild());
                }
                else if( StrX(childNode->getNodeName()).isEqual("info") )
                {
                    this->parseDrumKitInfo(childNode->getFirstChild());
                }
                else if( StrX(childNode->getNodeName()).isEqual("instrumentList") )
                {
                    this->parseDrumKitInstrumentList(childNode);
                }
            }
        }
    }
    
    void DrumKit::parseDrumKitAuthor(XERCES_CPP_NAMESPACE::DOMNode* domNode)
    {
        if(domNode->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE)
        {
            //debug
            //std::cout << StrX(domNode->getNodeValue()).StdString() << std::endl;
            
            //work
            this->author = new std::string(StrX(domNode->getNodeValue()).CString());
        }
    }
    
    void DrumKit::parseDrumKitName(XERCES_CPP_NAMESPACE::DOMNode* domNode)
    {
        if(domNode->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE)
        {
            //debug
            //std::cout << StrX(domNode->getNodeValue()).StdString() << std::endl;
            
            //work
            this->name = new std::string(StrX(domNode->getNodeValue()).CString());
        }
    }
    
    void DrumKit::parseDrumKitInfo(XERCES_CPP_NAMESPACE::DOMNode* domNode)
    {
        if(domNode->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE)
        {
            //debug
            //std::cout << StrX(domNode->getNodeValue()).StdString() << std::endl;
            
            //work
            this->info = new std::string(StrX(domNode->getNodeValue()).CString());
        }
    }
    
    void DrumKit::parseDrumKitInstrumentList(XERCES_CPP_NAMESPACE::DOMNode* domNode)
    {
        XERCES_CPP_NAMESPACE::DOMNodeList* childNodeList = domNode->getChildNodes();
        
        //parse all child elements and use all relevant information
        for(int i = 0; i<childNodeList->getLength(); i++)
        {
            //get node
            XERCES_CPP_NAMESPACE::DOMNode* childNode = childNodeList->item(i);
            
            //work
            if(childNode->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
            {
                //debug
                //std::cout << StrX(childNode->getNodeName()).StdString() << std::endl;
                
                //work
                if( StrX(childNode->getNodeName()).isEqual("instrument") )
                {
                    try
                    {
                        this->instrumentList.push_back( new Instrument(childNode, this->path) );
                    }
                    catch (const std::logic_error& e)
                    {
                        std::cerr << "Instrument could not be loaded." << std::endl;
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
        } 
    }
    
    SoundElement* DrumKit::cloneSoundElementWithVolume(instrument_id instrumentID, float vol)
    {
        for(std::list<Instrument*>::iterator it = this->instrumentList.begin(); it != this->instrumentList.end(); it++)
        {
            //debug
            //std::cout << (*it)->getId() << std::endl;
            
            //work
            if( (*it)->getId() == instrumentID )
            {
                SoundElement* ret = (*it)->cloneSoundElementWithVolume(vol);
                
                if(ret != NULL)
                    ret->instrumentID = instrumentID;
                
                return ret;
            }
        }
        
        std::cout << "no SoundElement for instrumentID: " << instrumentID << std::endl;
        
        return NULL;
    }
    
    void DrumKit::loadAllSoundFiles()
    {
        for(std::list<Instrument*>::iterator it = this->instrumentList.begin(); it != this->instrumentList.end(); it++)
        {
            (*it)->loadAllSoundFiles();
        }
    }
    
    std::string DrumKit::getDrumKitName()
    {
        if(this->name != NULL)
            return *this->name;
        else
            return std::string();
    }
    
    std::string DrumKit::getInstrumentName(instrument_id instrumentID)
    {
        for(std::list<Instrument*>::iterator it = this->instrumentList.begin(); it != this->instrumentList.end(); it++)
        {
            //debug
            //std::cout << (*it)->getId() << std::endl;
            
            //work
            if( (*it)->getId() == instrumentID )
            {
                return (*it)->getName();
            }
        }
        
        return std::string();
    }
    
    std::list<SoundInformation>* DrumKit::getListOfAllSoundInformations() const
    {
        std::list<SoundInformation>* ret = new std::list<SoundInformation>();
        
        for(std::list<Instrument*>::const_iterator it = this->instrumentList.begin(); it != this->instrumentList.end(); it++)
        {
            SoundInformation si;
            si.drumkitID = -1;
            si.instrumentID = (*it)->getId();
            si.name = (*it)->getName();
            ret->push_back(si);
        }
        
        //return
        return ret;
    }
    
    instrument_id DrumKit::getInstrumentID(std::string name)
    {
        for(std::list<Instrument*>::iterator it = this->instrumentList.begin(); it != this->instrumentList.end(); it++)
        {
            if( (*it)->getName() == name )
                return (*it)->getId();
        }
        
        throw std::logic_error("Instrument not found.");
        return 0; //avoid warning
    }

} //namespace libTheClick
