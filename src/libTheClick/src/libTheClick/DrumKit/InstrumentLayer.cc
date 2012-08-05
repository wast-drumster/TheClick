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

#include "libTheClick/DrumKit/InstrumentLayer.h"
#include "libTheClick/definitions.h"
#include "libTheClick/helper/Xerces/StrX.h"
//#include "libTheClick/helper/Xerces/StrX.h"
//#include "libTheClick/helper/Xerces/DOMTreeErrorHandler.h"

//#include <stdexcept>

//DEBUG
#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    InstrumentLayer::InstrumentLayer(std::string* fileName, float min, float max, std::string* path)
    {
        this->soundElement = NULL;
        this->path = new std::string(*path);
        this->fileName = new std::string(*fileName);
        this->min = min;
        this->max = max;
    }

    InstrumentLayer::InstrumentLayer(XERCES_CPP_NAMESPACE::DOMNode* domNode, std::string* path)
    {
        //initialize attributes
        this->soundElement = NULL;
        this->path = new std::string(*path);
        
        //preparation
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
                if( StrX(childNode->getNodeName()).isEqual("filename") )
                {
                    this->fileName = new std::string( StrX(childNode->getFirstChild()->getNodeValue()).StdString() );
                } 
                else if( StrX(childNode->getNodeName()).isEqual("min") )
                {
                    this->min = atof( StrX(childNode->getFirstChild()->getNodeValue()).CString() );
                }
                else if( StrX(childNode->getNodeName()).isEqual("max") )
                {
                    this->max = atof( StrX(childNode->getFirstChild()->getNodeValue()).CString() );
                }
            }
        }
    }

    InstrumentLayer::~InstrumentLayer()
    {
        //delete attributes
        if(this->fileName != NULL)
            delete this->fileName;
        
        if(this->path != NULL)
            delete this->path;
        
        if(this->soundElement != NULL)
            delete this->soundElement;
    }
        
    //*****************************
    //********** METHODS **********
    //*****************************
    SoundElement* InstrumentLayer::cloneSoundElementWithVolume(float vol)
    {
        //check if sound file is already loaded
        this->loadSoundFile();
        
        //clone SoundElement
        SoundElement* ret = this->soundElement->clone();
        
        if(ret != NULL)
            ret->multiplayVolumeWith(vol);
        
        //return
        return ret;
    }
    
    const float& InstrumentLayer::getMin() const
    {
        return this->min;
    }
    
    const float& InstrumentLayer::getMax() const
    {
        return this->max;
    }
    
    void InstrumentLayer::loadSoundFile()
    {
        //check if sound file is already loaded
        if(this->soundElement == NULL)
        {
            std::string localPath( *this->path );
            localPath.append( "/" );
            localPath.append( *this->fileName );
            
            try
            {
                this->soundElement = new SoundElement( -1, -1, localPath, 1.0 );
            }
            catch (...)
            {
                this->soundElement = NULL;
            }
        }
    }

    void InstrumentLayer::freeMemory()
    {
        if(this->soundElement != NULL)
        {
            SoundElement* tmp = this->soundElement;
            this->soundElement = NULL;
            delete tmp;
        }
    }
    
    bool InstrumentLayer::soundElementIsUnique()
    {
        if(this->soundElement == NULL)
            return 0;
        else
            return this->soundElement->soundElementIsUnique();
    }
    
} //namespace libTheClick
