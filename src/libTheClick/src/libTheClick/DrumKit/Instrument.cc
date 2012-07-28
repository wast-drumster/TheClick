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

#include "libTheClick/DrumKit/Instrument.h"
#include "libTheClick/definitions.h"
#include "libTheClick/helper/Xerces/StrX.h"
//#include "libTheClick/helper/Xerces/StrX.h"
//#include "libTheClick/helper/Xerces/DOMTreeErrorHandler.h"

#include <stdexcept>
//#include <boost/thread/thread.hpp> //for this_thread::sleep()
#include "boost/bind.hpp"

//DEBUG
#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    Instrument::Instrument(XERCES_CPP_NAMESPACE::DOMNode* domNode, std::string* path)
    {
        //check wather there are excludes
//        if( this->checkWatherThereAreExcludes(domNode) )
//            throw std::logic_error("Instrument shoud be excluded.");
        
        //initialize attributes
        this->path = new std::string( *path );

        //preparation
        XERCES_CPP_NAMESPACE::DOMNodeList* childNodeList = domNode->getChildNodes();
        
        //create instrument layers
        if( this->checkWatherThereAreLayers(domNode) )
        {
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
                    if( StrX(childNode->getNodeName()).isEqual("name") )
                    {
                        this->name = new std::string( StrX(childNode->getFirstChild()->getNodeValue()).StdString() );
                        
                        //debug
                        //std::cout << *this->name << std::endl;
                    }
                    else if( StrX(childNode->getNodeName()).isEqual("layer") )
                    {
                        this->instrumentLayerList.push_back( new InstrumentLayer(childNode, this->path) );
                    }
                    else if( StrX(childNode->getNodeName()).isEqual("id") )
                    {
                        this->id = atoi( StrX(childNode->getFirstChild()->getNodeValue()).CString() );
                    }
                }
            }
        }
        else //no layer
        {
            std::string* fileName = NULL;
            float min = 0.0f;
            float max = 1.0f;
            
            //parse all child elements and use all relevant information
            for(int i = 0; i<childNodeList->getLength(); i++)
            {
                //get node
                XERCES_CPP_NAMESPACE::DOMNode* childNode = childNodeList->item(i);
                
                //check for cerrectnes
                if(childNode->getFirstChild() == NULL)
                {
                    delete this->path;
                    throw std::logic_error("ChildNode->getFirstChild() is NULL.");
                }
                
                //work
                if(childNode->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
                {
                    //debug
                    //std::cout << StrX(childNode->getNodeName()).StdString() << std::endl;
                    
                    //work
                    if( StrX(childNode->getNodeName()).isEqual("name") )
                    {
                        this->name = new std::string( StrX(childNode->getFirstChild()->getNodeValue()).StdString() );
                        
                        //debug
                        //std::cout << *this->name << std::endl;
                    }
                    else if( StrX(childNode->getNodeName()).isEqual("filename") )
                    {
                        fileName = new std::string( StrX(childNode->getFirstChild()->getNodeValue()).StdString() );
                    }
                    else if( StrX(childNode->getNodeName()).isEqual("min") )
                    {
                        min = atof( StrX(childNode->getFirstChild()->getNodeValue()).CString() );
                    }
                    else if( StrX(childNode->getNodeName()).isEqual("max") )
                    {
                        max = atof( StrX(childNode->getFirstChild()->getNodeValue()).CString() );
                    }
                    else if( StrX(childNode->getNodeName()).isEqual("id") )
                    {
                        this->id = atoi( StrX(childNode->getFirstChild()->getNodeValue()).CString() );
                    }
                }
            }
            
            //create single layer
            if(fileName != NULL)
            {
                this->instrumentLayerList.push_back( new InstrumentLayer(fileName, min, max, this->path) );
            }
            else
            {
                throw std::logic_error("no filename for instrument");
            }
        }
        
        //create garbage collector thread
        this->garbageCollectorThreadShouldStop = false;
        this->garbageCollectorThread = new boost::thread( boost::bind( &Instrument::garbageCollectorWorkerFunction, &(*this) ) );
    }

    Instrument::~Instrument()
    {
        //delete attributes
        if(this->name != NULL)
            delete this->name;
        
        if(this->path != NULL)
            delete this->path;
        
        //delete elements in instrumentLayerList
        for(std::list<InstrumentLayer*>::iterator it = this->instrumentLayerList.begin(); it != this->instrumentLayerList.end(); /*nothing*/)
        {
            it = this->instrumentLayerList.erase(it);
            
            //end condition
            if(it == this->instrumentLayerList.end()) break;
        }
        
        //terminate thread
        if(this->garbageCollectorThread != NULL)
        {
            this->garbageCollectorThreadShouldStop = true;
            this->garbageCollectorThread->join();
            delete this->garbageCollectorThread;
        }
    }
        
    //*****************************
    //********** METHODS **********
    //*****************************
    bool Instrument::checkWatherThereAreLayers(XERCES_CPP_NAMESPACE::DOMNode* domNode) const
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
                if( StrX(childNode->getNodeName()).isEqual("layer") )
                    return true;
            }
        }    
        
        //no DOMNote with name 'layer' detected
        return false;
    }
    
    SoundElement* Instrument::cloneSoundElementWithVolume(float vol)
    {
        for(std::list<InstrumentLayer*>::iterator it = this->instrumentLayerList.begin(); it != this->instrumentLayerList.end(); it++)
        {
            if( vol >= (*it)->getMin() &&
                vol <= (*it)->getMax() )
            {
                return (*it)->cloneSoundElementWithVolume(vol);
            }
        }
        
        return NULL;
    }
    
    const int32_t Instrument::getId() const
    {
        return this->id;
    }
    
    void Instrument::loadAllSoundFiles()
    {
        for(std::list<InstrumentLayer*>::iterator it = this->instrumentLayerList.begin(); it != this->instrumentLayerList.end(); it++)
        {
            (*it)->loadSoundFile();
        }
    }
    
    void Instrument::garbageCollectorWorkerFunction()
    {
        //debug
//        std::cout << "Thread: " << *this->name << std::endl;
        
        //run until object should be deleted
        while( !this->garbageCollectorThreadShouldStop )
        {
            //sleep
            boost::this_thread::sleep( boost::posix_time::milliseconds(10*1000) );
            
            //delete SoundElement which are not required any more
            for(std::list<InstrumentLayer*>::iterator it = this->instrumentLayerList.begin(); it != this->instrumentLayerList.end(); it++)
            {
                //debug
//                std::cout << "Sound check: " << *this->name << " min: " << (*it)->getMin() << " max: " << (*it)->getMax() << std::endl;
                
                if( (*it)->soundElementIsUnique() )
                {
                    (*it)->freeMemory();
                    std::cout << "Sound deleted: " << *this->name << " min: " << (*it)->getMin() << " max: " << (*it)->getMax() << std::endl;
                }
            }
            
        }
    }
    
} //namespace libTheClick
