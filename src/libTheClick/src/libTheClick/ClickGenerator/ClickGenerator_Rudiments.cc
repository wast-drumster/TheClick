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

#include "libTheClick/ClickGenerator/ClickGenerator_Rudiments.h"
#include "libTheClick/definitions.h"
#include "libTheClick/SoundBase.h"

#include <stdexcept>

//DEBUG
//#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    ClickGenerator_Rudiments::ClickGenerator_Rudiments()
    {
        //initialize
        this->clickConfiguration = NULL;
        this->rudimentsID = 10;
        
        this->rNormalSoundElement = NULL;
        this->rGhostSoundElement = NULL;
        this->rAccentSoundElement = NULL;
        this->lNormalSoundElement = NULL;
        this->lGhostSoundElement = NULL;
        this->lAccentSoundElement = NULL;

        //reset
        this->reset();
    }
    
    ClickGenerator_Rudiments::~ClickGenerator_Rudiments()
    {
        //delete attributes
        if(this->rNormalSoundElement != NULL)
            delete this->rNormalSoundElement;

        if(this->rGhostSoundElement != NULL)
            delete this->rGhostSoundElement;
        
        if(this->rAccentSoundElement != NULL)
            delete this->rAccentSoundElement;
        
        if(this->lNormalSoundElement != NULL)
            delete this->lNormalSoundElement;
        
        if(this->lGhostSoundElement != NULL)
            delete this->lGhostSoundElement;
        
        if(this->lAccentSoundElement != NULL)
            delete this->lAccentSoundElement;
    }
    
    //*****************************
    //********** METHODS **********
    //*****************************
    void ClickGenerator_Rudiments::reset()
    {
        //reset attributes
        this->lastBeatTime = 0;
        this->soundElementGenerationHasStarted = false;
        
        //remove all elements in soundElementList
        for (std::list<SoundElement*>::iterator it=this->soundElementList.begin(); it != this->soundElementList.end(); /*nothing*/)
        {
            delete *it;
            it = this->soundElementList.erase(it);
        }  
    }
    
    int32_t ClickGenerator_Rudiments::getRudimentsID() const
    {
        return this->rudimentsID;
    }
    
    void ClickGenerator_Rudiments::setRudimentsID(int32_t value)
    {
        //check correctnes
        if(value < 1 || value > 40)
            throw std::logic_error("Value must be between 1 and 40.");
        
        //take value
        this->rudimentsID
        = value;
    }
    
    SoundElement* ClickGenerator_Rudiments::getSoundElement(hand h, accentuation a) const
    {
        if(h == RIGHT)
        {
            if(a == NORMAL)
                return this->rNormalSoundElement;
            else if(a == GHOST)
                return this->rGhostSoundElement;
            else if(a == ACCENT)
                return this->rAccentSoundElement;
        }
        else if(h == LEFT)
        {
            if(a == NORMAL)
                return this->lNormalSoundElement;
            else if(a == GHOST)
                return this->lGhostSoundElement;
            else if(a == ACCENT)
                return this->lAccentSoundElement;
        }
        
        //shout never happen
        return NULL;
    }
    
    void ClickGenerator_Rudiments::setSoundElement(hand h, accentuation a, SoundElement* se)
    {
        if(h == RIGHT)
        {
            if(a == NORMAL)
            {
                if(this->rNormalSoundElement != NULL)
                    delete this->rNormalSoundElement;
                
                this->rNormalSoundElement = se;
            }
            else if(a == GHOST)
            {
                if(this->rGhostSoundElement != NULL)
                    delete this->rGhostSoundElement;
                
                this->rGhostSoundElement = se;   
            }
            else if(a == ACCENT)
            {
                if(this->rAccentSoundElement != NULL)
                    delete this->rAccentSoundElement;
                
                this->rAccentSoundElement = se;
            }        
        }
        else if(h == LEFT)
        {
            if(a == NORMAL)
            {
                if(this->lNormalSoundElement != NULL)
                    delete this->lNormalSoundElement;
                
                this->lNormalSoundElement = se;
            }
            else if(a == GHOST)
            {
                if(this->lGhostSoundElement != NULL)
                    delete this->lGhostSoundElement;
                
                this->lGhostSoundElement = se;
            }
            else if(a == ACCENT)
            {
                if(this->lAccentSoundElement != NULL)
                    delete this->lAccentSoundElement;
                
                this->lAccentSoundElement = se;
            }
        }
    }
    
    void ClickGenerator_Rudiments::generateSoundElements(int64_t endTime)
    {
        //calculate first beatIndex
        int32_t beatIndex = 0;
        if(this->soundElementGenerationHasStarted)
            beatIndex = (this->clickConfiguration->getReferenceBeatCount() + 1 + (this->lastBeatTime - this->clickConfiguration->getReferenceTime()) / this->clickConfiguration->getFramesPerBeat()) % this->getRudimentLength(this->rudimentsID);
        
        //fill SoundElementList
        while(this->lastBeatTime < endTime)
        {
            //calculate nextBeatTime
            int64_t nextBeatTime = 0;
            if(this->soundElementGenerationHasStarted)
                 nextBeatTime = this->lastBeatTime + this->clickConfiguration->getFramesPerBeat();
            
            //add sounds for right hand with normal accentuation
            if(this->rNormalSoundElement != NULL)
            {
                for(int32_t i = 0; i<this->getRudimentVectorLength(RIGHT, NORMAL, this->rudimentsID); i++)
                {
                    double timeValue = this->getRudimentTimeValues(RIGHT, NORMAL, this->rudimentsID)[i];
                    if( timeValue >= (double)(beatIndex + 1) && timeValue < (double)(beatIndex + 2) )
                    {
                        int64_t nextTime = nextBeatTime + (timeValue - (double)(beatIndex + 1)) * this->clickConfiguration->getFramesPerBeat();
                        this->soundElementList.push_back(this->rNormalSoundElement->cloneAndSetTime(nextTime));
                    }
                }
            }
            
            //add sounds for right hand with ghost accentuation
            if(this->rGhostSoundElement != NULL)
            {
                for(int32_t i = 0; i<this->getRudimentVectorLength(RIGHT, GHOST, this->rudimentsID); i++)
                {
                    double timeValue = this->getRudimentTimeValues(RIGHT, GHOST, this->rudimentsID)[i];
                    if( timeValue >= (double)(beatIndex + 1) && timeValue < (double)(beatIndex + 2) )
                    {
                        int64_t nextTime = nextBeatTime + (timeValue - (double)(beatIndex + 1)) * this->clickConfiguration->getFramesPerBeat();
                        this->soundElementList.push_back(this->rGhostSoundElement->cloneAndSetTime(nextTime));
                    }
                }
            }
            
            //add sounds for right hand with accent accentuation
            if(this->rAccentSoundElement != NULL)
            {
                for(int32_t i = 0; i<this->getRudimentVectorLength(RIGHT, ACCENT, this->rudimentsID); i++)
                {
                    double timeValue = this->getRudimentTimeValues(RIGHT, ACCENT, this->rudimentsID)[i];
                    if( timeValue >= (double)(beatIndex + 1) && timeValue < (double)(beatIndex + 2) )
                    {
                        int64_t nextTime = nextBeatTime + (timeValue - (double)(beatIndex + 1)) * this->clickConfiguration->getFramesPerBeat();
                        this->soundElementList.push_back(this->rAccentSoundElement->cloneAndSetTime(nextTime));
                    }
                }
            }
            
            //add sounds for left hand with normal accentuation
            if(this->lNormalSoundElement != NULL)
            {
                for(int32_t i = 0; i<this->getRudimentVectorLength(LEFT, NORMAL, this->rudimentsID); i++)
                {
                    double timeValue = this->getRudimentTimeValues(LEFT, NORMAL, this->rudimentsID)[i];
                    if( timeValue >= (double)(beatIndex + 1) && timeValue < (double)(beatIndex + 2) )
                    {
                        int64_t nextTime = nextBeatTime + (timeValue - (double)(beatIndex + 1)) * this->clickConfiguration->getFramesPerBeat();
                        this->soundElementList.push_back(this->lNormalSoundElement->cloneAndSetTime(nextTime));
                    }
                }
            }
            
            //add sounds for left hand with ghost accentuation
            if(this->lGhostSoundElement != NULL)
            {
                for(int32_t i = 0; i<this->getRudimentVectorLength(LEFT, GHOST, this->rudimentsID); i++)
                {
                    double timeValue = this->getRudimentTimeValues(LEFT, GHOST, this->rudimentsID)[i];
                    if( timeValue >= (double)(beatIndex + 1) && timeValue < (double)(beatIndex + 2) )
                    {
                        int64_t nextTime = nextBeatTime + (timeValue - (double)(beatIndex + 1)) * this->clickConfiguration->getFramesPerBeat();
                        this->soundElementList.push_back(this->lGhostSoundElement->cloneAndSetTime(nextTime));
                    }
                }
            }
            
            //add sounds for left hand with accent accentuation
            if(this->lAccentSoundElement != NULL)
            {
                for(int32_t i = 0; i<this->getRudimentVectorLength(LEFT, ACCENT, this->rudimentsID); i++)
                {
                    double timeValue = this->getRudimentTimeValues(LEFT, ACCENT, this->rudimentsID)[i];
                    if( timeValue >= (double)(beatIndex + 1) && timeValue < (double)(beatIndex + 2) )
                    {
                        int64_t nextTime = nextBeatTime + (timeValue - (double)(beatIndex + 1)) * this->clickConfiguration->getFramesPerBeat();
                        this->soundElementList.push_back(this->lAccentSoundElement->cloneAndSetTime(nextTime));
                    }
                }
            }
            
            //increment lastBeatTime
            this->lastBeatTime = nextBeatTime;
            
            //increment beatIndex
            beatIndex = (beatIndex + 1) % this->getRudimentLength(this->rudimentsID);
            
            //indicate that SoundElement generation has started
            this->soundElementGenerationHasStarted = true;
        }
    }
    
    void ClickGenerator_Rudiments::setClickConfiguration(ClickConfiguration* cc)
    {
        this->clickConfiguration = cc;
        this->lastBeatTime = cc->getReferenceTime();
        this->cleanSoundElements();
    }
    
    ClickConfiguration* ClickGenerator_Rudiments::getClickConfiguration()
    {
        return this->clickConfiguration;
    }
    
    std::list<SoundElement*>* ClickGenerator_Rudiments::getSoundElementList(int64_t time)
    {
        //generate new elements for the future in soundElementList
        this->generateSoundElements( time );
        
        //return list
        return &this->soundElementList;
    }
    
    void ClickGenerator_Rudiments::cleanSoundElements()
    {
        //remove all elements in soundElementList which start in future
        for (std::list<SoundElement*>::iterator it=this->soundElementList.begin(); it != this->soundElementList.end(); /*nothing*/)
        {
            if( (*it)->time >= this->clickConfiguration->getReferenceTime() )
            {
                delete *it;
                it = this->soundElementList.erase(it);
            }
            else
            {
                it++;
            }
            
            //end condition
            if(it == this->soundElementList.end()) break;
        }
        
        //reset lastBeatTime
        if(this->soundElementGenerationHasStarted)
            this->lastBeatTime = this->clickConfiguration->getReferenceTime() - this->clickConfiguration->getFramesPerBeat();
    }

    int32_t ClickGenerator_Rudiments::getRudimentLength(int32_t rudimentID) const
    {
        switch (rudimentID)
        {
            case 1: return 1; break;
            case 2: return 1; break;
            case 3: return 4; break;
            case 4: return 2; break;
            case 5: return 1; break;
            case 6: return 1; break;
            case 7: return 2; break;
            case 8: return 2; break;
            case 9: return 2; break;
            case 10: return 4; break;
            case 11: return 4; break;
            case 12: return 4; break;
            case 13: return 4; break;
            case 14: return 4; break;
            case 15: return 6; break;
            case 16: return 2; break;
            case 17: return 3; break;
            case 18: return 4; break;
            case 19: return 3; break;
            case 20: return 2; break;
            case 21: return 3; break;
            case 22: return 2; break;
            case 23: return 2; break;
            case 24: return 2; break;
            case 25: return 2; break;
            case 26: return 3; break;
            case 27: return 2; break;
            case 28: return 1; break;
            case 29: return 2; break;
            case 30: return 3; break;
            case 31: return 2; break;
            case 32: return 2; break;
            case 33: return 3; break;
            case 34: return 2; break;
            case 35: return 2; break;
            case 36: return 3; break;
            case 37: return 4; break;
            case 38: return 2; break;
            case 39: return 3; break;
            case 40: return 4; break;
            default: return 1; break;
        }
    }
    
    double* ClickGenerator_Rudiments::getRudimentTimeValues(hand h, accentuation a, int32_t rudimentID) const
    {
        static double rn1[] = {1.0, 1.5};
        static double rg1[] = {};
        static double ra1[] = {};
        static double ln1[] = {1.25, 1.75};
        static double lg1[] = {};
        static double la1[] = {};
                        
        static double rn2[] = {1.0, 1.0+2.0/6.0};
        static double rg2[] = {};
        static double ra2[] = {};
        static double ln2[] = {1.0+1.0/6.0, 1.5};
        static double lg2[] = {};
        static double la2[] = {};
                        
        static double rn3[] = {1.0, 1.0+2.0/6.0, 1.0+4.0/6.0, 2.0,  3.0+1.0/6.0, 3.0+3.0/6.0, 3.0+5.0/6.0};
        static double rg3[] = {};
        static double ra3[] = {};
        static double ln3[] = {1.0+1.0/6.0, 1.0+3.0/6.0, 1.0+5.0/6.0,  3.0, 3.0+2.0/6.0, 3.0+4.0/6.0, 4.0};
        static double lg3[] = {};
        static double la3[] = {};
                        
        static double rn4[] = {1.0+1.0/5.0, 1.0+2.0/5.0};
        static double rg4[] = {1.0+3.0/5.0, 1.0+4.0/5.0};
        static double ra4[] = {1.0};
        static double ln4[] = {1.0+1.0/5.0, 1.0+2.0/5.0};
        static double lg4[] = {1.0+3.0/5.0, 1.0+4.0/5.0};
        static double la4[] = {1.0};
                        
        static double rn5[] = {1.0, 1.0+1.0/6.0, 1.0+2.0/6.0};
        static double rg5[] = {};
        static double ra5[] = {};
        static double ln5[] = {1.5, 1.5+1.0/6.0, 1.5+2.0/6.0};
        static double lg5[] = {};
        static double la5[] = {};
                        
        static double rn6[] = {1.0, 1.125,  1.5, 1.625};
        static double rg6[] = {};
        static double ra6[] = {};
        static double ln6[] = {1.25, 1.375,  1.75, 1.875};
        static double lg6[] = {};
        static double la6[] = {};
                        
        static double rn7[] = {1.0, 1.125,  2.0, 2.125};
        static double rg7[] = {};
        static double ra7[] = {1.5};
        static double ln7[] = {1.25, 1.375,  2.25, 2.375};
        static double lg7[] = {};
        static double la7[] = {2.5};
                        
        static double rn8[] = {1.5, 1.625,  2.5, 2.625};
        static double rg8[] = {};
        static double ra8[] = {1.0, 2.0};
        static double ln8[] = {1.25, 1.375,  2.25, 2.375};
        static double lg8[] = {};
        static double la8[] = {1.75, 2.75};
                        
        static double rn9[] = {1.0, 1.125, 1.5, 1.625,  2.0, 2.125, 2.5, 2.625};
        static double rg9[] = {};
        static double ra9[] = {};
        static double ln9[] = {1.25, 1.375,  2.25, 2.375};
        static double lg9[] = {};
        static double la9[] = {1.75, 2.75};
        
        static double rn10[] = {1.0, 1.125, 1.5, 1.625,  3.25, 3.375, 3.75, 3.875};
        static double rg10[] = {};
        static double ra10[] = {2.0};
        static double ln10[] = {1.25, 1.375, 1.75, 1.875,  3.0, 3.125, 3.5, 3.625};
        static double lg10[] = {};
        static double la10[] = {4.0};

        static double rn11[] = {1.0, 1.125, 1.5, 1.625,  3.25, 3.375, 3.75, 3.875};
        static double rg11[] = {};
        static double ra11[] = {2.0, 4.25};
        static double ln11[] = {1.25, 1.375, 1.75, 1.875,  3.0, 3.125, 3.5, 3.625};
        static double lg11[] = {};
        static double la11[] = {2.25, 4.0};

        static double rn12[] = {1.0, 1.125, 1.5, 1.625, 2.0, 2.125,  3.25, 3.375, 3.75, 3.875};
        static double rg12[] = {};
        static double ra12[] = {4.25};
        static double ln12[] = {1.25, 1.375, 1.75, 1.875,  3.0, 3.125, 3.5, 3.625, 4.0, 4.125};
        static double lg12[] = {};
        static double la12[] = {2.25};

        static double rn13[] = {1.0, 1.125, 1.5, 1.625, 2.0, 2.125,  3.25, 3.375, 3.75, 3.875, 4.25, 4.375};
        static double rg13[] = {};
        static double ra13[] = {2.5};
        static double ln13[] = {1.25, 1.375, 1.75, 1.875, 2.25, 2.375,  3.0, 3.125, 3.5, 3.625, 4.0, 4.125};
        static double lg13[] = {};
        static double la13[] = {4.5};

        static double rn14[] = {1.0, 1.125, 1.5, 1.625, 2.0, 2.125, 2.5, 2.625,  3.25, 3.375, 3.75, 3.875, 4.25, 4.375};
        static double rg14[] = {};
        static double ra14[] = {4.75};
        static double ln14[] = {1.25, 1.375, 1.75, 1.875, 2.25, 2.375,  3.0, 3.125, 3.5, 3.625, 4.0, 4.125, 4.5, 4.625};
        static double lg14[] = {};
        static double la14[] = {2.75};

        static double rn15[] = {1.0, 1.125, 1.5, 1.625, 2.0, 2.125, 2.5, 2.625,  4.25, 4.375, 4.75, 4.875, 5.25, 5.375, 5.75, 5.875};
        static double rg15[] = {};
        static double ra15[] = {3.0};
        static double ln15[] = {1.25, 1.375, 1.75, 1.875, 2.25, 2.375, 2.75, 2.875,  4.0, 4.125, 4.5, 4.625, 5.0, 5.125, 5.5, 5.625};
        static double lg15[] = {};
        static double la15[] = {6.0};
        

        static double rn16[] = {1.5, 1.75, 2.25};
        static double rg16[] = {};
        static double ra16[] = {1.0};
        static double ln16[] = {1.25, 2.5, 2.75};
        static double lg16[] = {};
        static double la16[] = {2.0};

        static double rn17[] = {1.5, 2.0, 2.25, 2.75, 3.25};
        static double rg17[] = {};
        static double ra17[] = {1.0};
        static double ln17[] = {1.25, 1.75, 3.0, 3.5, 3.75};
        static double lg17[] = {};
        static double la17[] = {2.5};

        static double rn18[] = {1.5, 2.0, 2.5, 2.75, 3.25, 3.75, 4.25};
        static double rg18[] = {};
        static double ra18[] = {1.0};
        static double ln18[] = {1.25, 1.75, 2.25, 3.5, 4.0, 4.5, 4.75};
        static double lg18[] = {};
        static double la18[] = {3.0};

        static double rn19[] = {1.5, 1.75, 3.0, 3.25};
        static double rg19[] = {};
        static double ra19[] = {1.0, 2.5};
        static double ln19[] = {1.25, 2.0, 2.25, 2.75, 3.5, 3.75};
        static double lg19[] = {};
        static double la19[] = {};
        
        static double rn20[] = {1.0};
        static double rg20[] = {1.98};
        static double ra20[] = {};
        static double ln20[] = {2.0};
        static double lg20[] = {2.98};
        static double la20[] = {};

        static double rn21[] = {2.0, 3.0};
        static double rg21[] = {2.48};
        static double ra21[] = {1.0};
        static double ln21[] = {1.5, 3.5};
        static double lg21[] = {2.98};
        static double la21[] = {2.5};

        static double rn22[] = {1.25, 2.25};
        static double rg22[] = {1.48, 2.48};
        static double ra22[] = {1.0, 2.0};
        static double ln22[] = {1.75, 2.75};
        static double lg22[] = {2.98, 1.98};
        static double la22[] = {1.5, 2.5};

        static double rn23[] = {1.0, 1.5, 2.0};
        static double rg23[] = {};
        static double ra23[] = {};
        static double ln23[] = {1.75};
        static double lg23[] = {2.98, 1.98};
        static double la23[] = {1.25};

        static double rn24[] = {1.5, 1.75, 2.25};
        static double rg24[] = {1.98};
        static double ra24[] = {1.0};
        static double ln24[] = {1.25, 2.5, 2.75};
        static double lg24[] = {2.98};
        static double la24[] = {2.0};

        static double rn25[] = {1.25, 1.75, 2.5};
        static double rg25[] = {1.98};
        static double ra25[] = {1.0};
        static double ln25[] = {1.5, 2.25, 2.75};
        static double lg25[] = {2.98};
        static double la25[] = {2.0};

        static double rn26[] = {1.5, 1.75, 2.75, 3.5, 3.75};
        static double rg26[] = {2.48};
        static double ra26[] = {1.0};
        static double ln26[] = {1.25, 2.0, 2.25, 3.0, 3.25};
        static double lg26[] = {3.98};
        static double la26[] = {2.5};

        static double rn27[] = {1.5, 2.5};
        static double rg27[] = {1.73, 2.73};
        static double ra27[] = {1.0, 2.0};
        static double ln27[] = {1.25, 2.25};
        static double lg27[] = {2.98, 1.98};
        static double la27[] = {1.75, 2.75};

        static double rn28[] = {1+1.0/6.0, 1.5+1.0/6.0};
        static double rg28[] = {};
        static double ra28[] = {1.0, 1.5};
        static double ln28[] = {1.0+2.0/6.0, 1.5+2.0/6.0};
        static double lg28[] = {1.98, 1.48};
        static double la28[] = {};

        static double rn29[] = {1.75, 2.75};
        static double rg29[] = {1.48, 2.48};
        static double ra29[] = {1.0, 2.0};
        static double ln29[] = {1.25, 2.25};
        static double lg29[] = {2.98, 1.98};
        static double la29[] = {1.5, 2.5};
        
        static double rn30[] = {2.0, 3.0, 3.25};
        static double rg30[] = {2.48};
        static double ra30[] = {1.0};
        static double ln30[] = {1.5, 1.75, 3.5};
        static double lg30[] = {3.98};
        static double la30[] = {2.5};

        static double rn31[] = {1.0};
        static double rg31[] = {1.8, 1.9};
        static double ra31[] = {};
        static double ln31[] = {2.0};
        static double lg31[] = {2.8, 2.9};
        static double la31[] = {};

        static double rn32[] = {1.0};
        static double rg32[] = {1.8, 1.9};
        static double ra32[] = {2.5};
        static double ln32[] = {2.0};
        static double lg32[] = {2.8, 2.9};
        static double la32[] = {1.5};

        static double rn33[] = {1.0, 1.5};
        static double rg33[] = {2.3, 2.4, 2.8, 2.9};
        static double ra33[] = {3.5};
        static double ln33[] = {2.5, 3.0};
        static double lg33[] = {3.8, 3.9, 1.3, 1.4};
        static double la33[] = {2.0};

        static double rn34[] = {1.0, 2.0};
        static double rg34[] = {};
        static double ra34[] = {1.5, 2.5};
        static double ln34[] = {1.25, 2.25};
        static double lg34[] = {2.8, 2.9, 1.8, 1.9};
        static double la34[] = {};

        static double rn35[] = {1.1, 1.5, 1.75, 2.25};
        static double rg35[] = {};
        static double ra35[] = {1.0};
        static double ln35[] = {1.25, 2.1, 2.5, 2.75};
        static double lg35[] = {};
        static double la35[] = {2.0};

        static double rn36[] = {1.5, 2.0, 2.25, 3.25};
        static double rg36[] = {2.8, 2.9};
        static double ra36[] = {1.0};
        static double ln36[] = {1.75, 3.0, 3.5, 3.75};
        static double lg36[] = {1.3, 1.4};
        static double la36[] = {2.5};

        static double rn37[] = {1.5, 2.0, 2.5, 2.75, 4.25};
        static double rg37[] = {3.3, 3.4, 3.8, 3.9};
        static double ra37[] = {1.0};
        static double ln37[] = {2.25, 3.5, 4.0, 4.5, 4.75};
        static double lg37[] = {1.3, 1.4, 1.8, 1.9};
        static double la37[] = {3.0};

        static double rn38[] = {1.0, 1.0+2.0/6.0, 2.0+1.0/6.0};
        static double rg38[] = {1.8, 1.9};
        static double ra38[] = {2.5};
        static double ln38[] = {1.0+1.0/6.0, 2.0, 2.0+2.0/6.0};
        static double lg38[] = {2.8, 2.9};
        static double la38[] = {1.5};

        static double rn39[] = {1.0, 1.5, 1.5+2.0/6.0, 3.0+1.0/6.0};
        static double rg39[] = {2.3, 2.4, 2.8, 2.9};
        static double ra39[] = {3.5};
        static double ln39[] = {1.5+1.0/6.0, 2.5, 3.0, 3.0+2.0/6.0};
        static double lg39[] = {3.8, 3.9, 1.3, 1.4};
        static double la39[] = {2.0};
        
        static double rn40[] = {1.0, 1.5, 2.0, 2.0+2.0/6.0, 4.0+1.0/6.0};
        static double rg40[] = {2.8, 2.9, 3.3, 3.4, 3.8, 3.9};
        static double ra40[] = {4.5};
        static double ln40[] = {2.0+1.0/6.0, 3.0, 3.5, 4.0, 4.0+2.0/6.0};
        static double lg40[] = {4.8, 4.9, 1.3, 1.4, 1.8, 1.9};
        static double la40[] = {2.5};
        
        double* v = NULL;
        
        if(h == RIGHT)
        {
            if(a == NORMAL)
                switch (rudimentID)
                {
                    case  1: v = rn1; break;
                    case  2: v = rn2; break;
                    case  3: v = rn3; break;
                    case  4: v = rn4; break;
                    case  5: v = rn5; break;
                    case  6: v = rn6; break;
                    case  7: v = rn7; break;
                    case  8: v = rn8; break;
                    case  9: v = rn9; break;
                    case 10: v = rn10; break;
                    case 11: v = rn11; break;
                    case 12: v = rn12; break;
                    case 13: v = rn13; break;
                    case 14: v = rn14; break;
                    case 15: v = rn15; break;
                    case 16: v = rn16; break;
                    case 17: v = rn17; break;
                    case 18: v = rn18; break;
                    case 19: v = rn19; break;
                    case 20: v = rn20; break;
                    case 21: v = rn21; break;
                    case 22: v = rn22; break;
                    case 23: v = rn23; break;
                    case 24: v = rn24; break;
                    case 25: v = rn25; break;
                    case 26: v = rn26; break;
                    case 27: v = rn27; break;
                    case 28: v = rn28; break;
                    case 29: v = rn29; break;
                    case 30: v = rn30; break;
                    case 31: v = rn31; break;
                    case 32: v = rn32; break;
                    case 33: v = rn33; break;
                    case 34: v = rn34; break;
                    case 35: v = rn35; break;
                    case 36: v = rn36; break;
                    case 37: v = rn37; break;
                    case 38: v = rn38; break;
                    case 39: v = rn39; break;
                    case 40: v = rn40; break;
                    default: return NULL; break;
                }
            else if(a == GHOST)
                switch (rudimentID)
                {
                    case  1: v = rg1; break;
                    case  2: v = rg2; break;
                    case  3: v = rg3; break;
                    case  4: v = rg4; break;
                    case  5: v = rg5; break;
                    case  6: v = rg6; break;
                    case  7: v = rg7; break;
                    case  8: v = rg8; break;
                    case  9: v = rg9; break;
                    case 10: v = rg10; break;
                    case 11: v = rg11; break;
                    case 12: v = rg12; break;
                    case 13: v = rg13; break;
                    case 14: v = rg14; break;
                    case 15: v = rg15; break;
                    case 16: v = rg16; break;
                    case 17: v = rg17; break;
                    case 18: v = rg18; break;
                    case 19: v = rg19; break;
                    case 20: v = rg20; break;
                    case 21: v = rg21; break;
                    case 22: v = rg22; break;
                    case 23: v = rg23; break;
                    case 24: v = rg24; break;
                    case 25: v = rg25; break;
                    case 26: v = rg26; break;
                    case 27: v = rg27; break;
                    case 28: v = rg28; break;
                    case 29: v = rg29; break;
                    case 30: v = rg30; break;
                    case 31: v = rg31; break;
                    case 32: v = rg32; break;
                    case 33: v = rg33; break;
                    case 34: v = rg34; break;
                    case 35: v = rg35; break;
                    case 36: v = rg36; break;
                    case 37: v = rg37; break;
                    case 38: v = rg38; break;
                    case 39: v = rg39; break;
                    case 40: v = rg40; break;
                    default: return NULL; break;
                }
            else if(a == ACCENT)
                switch (rudimentID)
                {
                    case  1: v = ra1; break;
                    case  2: v = ra2; break;
                    case  3: v = ra3; break;
                    case  4: v = ra4; break;
                    case  5: v = ra5; break;
                    case  6: v = ra6; break;
                    case  7: v = ra7; break;
                    case  8: v = ra8; break;
                    case  9: v = ra9; break;
                    case 10: v = ra10; break;
                    case 11: v = ra11; break;
                    case 12: v = ra12; break;
                    case 13: v = ra13; break;
                    case 14: v = ra14; break;
                    case 15: v = ra15; break;
                    case 16: v = ra16; break;
                    case 17: v = ra17; break;
                    case 18: v = ra18; break;
                    case 19: v = ra19; break;
                    case 20: v = ra20; break;
                    case 21: v = ra21; break;
                    case 22: v = ra22; break;
                    case 23: v = ra23; break;
                    case 24: v = ra24; break;
                    case 25: v = ra25; break;
                    case 26: v = ra26; break;
                    case 27: v = ra27; break;
                    case 28: v = ra28; break;
                    case 29: v = ra29; break;
                    case 30: v = ra30; break;
                    case 31: v = ra31; break;
                    case 32: v = ra32; break;
                    case 33: v = ra33; break;
                    case 34: v = ra34; break;
                    case 35: v = ra35; break;
                    case 36: v = ra36; break;
                    case 37: v = ra37; break;
                    case 38: v = ra38; break;
                    case 39: v = ra39; break;
                    case 40: v = ra40; break;
                    default: return NULL; break;
                }
        }
        else if(h == LEFT)
        {
            if(a == NORMAL)
                switch (rudimentID)
                {
                    case  1: v = ln1; break;
                    case  2: v = ln2; break;
                    case  3: v = ln3; break;
                    case  4: v = ln4; break;
                    case  5: v = ln5; break;
                    case  6: v = ln6; break;
                    case  7: v = ln7; break;
                    case  8: v = ln8; break;
                    case  9: v = ln9; break;
                    case 10: v = ln10; break;
                    case 11: v = ln11; break;
                    case 12: v = ln12; break;
                    case 13: v = ln13; break;
                    case 14: v = ln14; break;
                    case 15: v = ln15; break;
                    case 16: v = ln16; break;
                    case 17: v = ln17; break;
                    case 18: v = ln18; break;
                    case 19: v = ln19; break;
                    case 20: v = ln20; break;
                    case 21: v = ln21; break;
                    case 22: v = ln22; break;
                    case 23: v = ln23; break;
                    case 24: v = ln24; break;
                    case 25: v = ln25; break;
                    case 26: v = ln26; break;
                    case 27: v = ln27; break;
                    case 28: v = ln28; break;
                    case 29: v = ln29; break;
                    case 30: v = ln30; break;
                    case 31: v = ln31; break;
                    case 32: v = ln32; break;
                    case 33: v = ln33; break;
                    case 34: v = ln34; break;
                    case 35: v = ln35; break;
                    case 36: v = ln36; break;
                    case 37: v = ln37; break;
                    case 38: v = ln38; break;
                    case 39: v = ln39; break;
                    case 40: v = ln40; break;
                    default: return NULL; break;
                }
            else if(a == GHOST)
                switch (rudimentID)
                {
                    case  1: v = lg1; break;
                    case  2: v = lg2; break;
                    case  3: v = lg3; break;
                    case  4: v = lg4; break;
                    case  5: v = lg5; break;
                    case  6: v = lg6; break;
                    case  7: v = lg7; break;
                    case  8: v = lg8; break;
                    case  9: v = lg9; break;
                    case 10: v = lg10; break;
                    case 11: v = lg11; break;
                    case 12: v = lg12; break;
                    case 13: v = lg13; break;
                    case 14: v = lg14; break;
                    case 15: v = lg15; break;
                    case 16: v = lg16; break;
                    case 17: v = lg17; break;
                    case 18: v = lg18; break;
                    case 19: v = lg19; break;
                    case 20: v = lg20; break;
                    case 21: v = lg21; break;
                    case 22: v = lg22; break;
                    case 23: v = lg23; break;
                    case 24: v = lg24; break;
                    case 25: v = lg25; break;
                    case 26: v = lg26; break;
                    case 27: v = lg27; break;
                    case 28: v = lg28; break;
                    case 29: v = lg29; break;
                    case 30: v = lg30; break;
                    case 31: v = lg31; break;
                    case 32: v = lg32; break;
                    case 33: v = lg33; break;
                    case 34: v = lg34; break;
                    case 35: v = lg35; break;
                    case 36: v = lg36; break;
                    case 37: v = lg37; break;
                    case 38: v = lg38; break;
                    case 39: v = lg39; break;
                    case 40: v = lg40; break;
                    default: return NULL; break;
                }
            else if(a == ACCENT)
                switch (rudimentID)
                {
                    case  1: v = la1; break;
                    case  2: v = la2; break;
                    case  3: v = la3; break;
                    case  4: v = la4; break;
                    case  5: v = la5; break;
                    case  6: v = la6; break;
                    case  7: v = la7; break;
                    case  8: v = la8; break;
                    case  9: v = la9; break;
                    case 10: v = la10; break;
                    case 11: v = la11; break;
                    case 12: v = la12; break;
                    case 13: v = la13; break;
                    case 14: v = la14; break;
                    case 15: v = la15; break;
                    case 16: v = la16; break;
                    case 17: v = la17; break;
                    case 18: v = la18; break;
                    case 19: v = la19; break;
                    case 20: v = la20; break;
                    case 21: v = la21; break;
                    case 22: v = la22; break;
                    case 23: v = la23; break;
                    case 24: v = la24; break;
                    case 25: v = la25; break;
                    case 26: v = la26; break;
                    case 27: v = la27; break;
                    case 28: v = la28; break;
                    case 29: v = la29; break;
                    case 30: v = la30; break;
                    case 31: v = la31; break;
                    case 32: v = la32; break;
                    case 33: v = la33; break;
                    case 34: v = la34; break;
                    case 35: v = la35; break;
                    case 36: v = la36; break;
                    case 37: v = la37; break;
                    case 38: v = la38; break;
                    case 39: v = la39; break;
                    case 40: v = la40; break;
                    default: return NULL; break;
                }
        }
        
        return v;
    }
    
    int32_t ClickGenerator_Rudiments::getRudimentVectorLength(hand h, accentuation a, int32_t rudimentID) const
    {
        if(h == RIGHT)
        {
            if(a == NORMAL)
                switch (rudimentID)
            {
                case 1: return 2; break;
                case 2: return 2; break;
                case 3: return 7; break;
                case 4: return 2; break;
                case 5: return 3; break;
                case 6: return 4; break;
                case 7: return 4; break;
                case 8: return 4; break;
                case 9: return 8; break;
                case 10: return 8; break;
                case 11: return 8; break;
                case 12: return 10; break;
                case 13: return 12; break;
                case 14: return 14; break;
                case 15: return 16; break;
                case 16: return 3; break;
                case 17: return 5; break;
                case 18: return 7; break;
                case 19: return 4; break;
                case 20: return 1; break;
                case 21: return 2; break;
                case 22: return 2; break;
                case 23: return 3; break;
                case 24: return 3; break;
                case 25: return 3; break;
                case 26: return 5; break;
                case 27: return 2; break;
                case 28: return 2; break;
                case 29: return 2; break;
                case 30: return 3; break;
                case 31: return 1; break;
                case 32: return 1; break;
                case 33: return 2; break;
                case 34: return 2; break;
                case 35: return 4; break;
                case 36: return 4; break;
                case 37: return 5; break;
                case 38: return 3; break;
                case 39: return 4; break;
                case 40: return 5; break;
                default: return 0; break;
            }
            else if(a == GHOST)
                switch (rudimentID)
            {
                case 1: return 0; break;
                case 2: return 0; break;
                case 3: return 0; break;
                case 4: return 2; break;
                case 5: return 0; break;
                case 6: return 0; break;
                case 7: return 0; break;
                case 8: return 0; break;
                case 9: return 0; break;
                case 10: return 0; break;
                case 11: return 0; break;
                case 12: return 0; break;
                case 13: return 0; break;
                case 14: return 0; break;
                case 15: return 0; break;
                case 16: return 0; break;
                case 17: return 0; break;
                case 18: return 0; break;
                case 19: return 0; break;
                case 20: return 1; break;
                case 21: return 1; break;
                case 22: return 2; break;
                case 23: return 0; break;
                case 24: return 1; break;
                case 25: return 1; break;
                case 26: return 1; break;
                case 27: return 2; break;
                case 28: return 0; break;
                case 29: return 2; break;
                case 30: return 1; break;
                case 31: return 2; break;
                case 32: return 2; break;
                case 33: return 4; break;
                case 34: return 0; break;
                case 35: return 0; break;
                case 36: return 2; break;
                case 37: return 4; break;
                case 38: return 2; break;
                case 39: return 4; break;
                case 40: return 6; break;
                default: return 0; break;
            }
            else if(a == ACCENT)
                switch (rudimentID)
            {
                case 1: return 0; break;
                case 2: return 0; break;
                case 3: return 0; break;
                case 4: return 1; break;
                case 5: return 0; break;
                case 6: return 0; break;
                case 7: return 1; break;
                case 8: return 2; break;
                case 9: return 0; break;
                case 10: return 1; break;
                case 11: return 2; break;
                case 12: return 1; break;
                case 13: return 1; break;
                case 14: return 1; break;
                case 15: return 1; break;
                case 16: return 1; break;
                case 17: return 1; break;
                case 18: return 1; break;
                case 19: return 2; break;
                case 20: return 0; break;
                case 21: return 1; break;
                case 22: return 2; break;
                case 23: return 1; break;
                case 24: return 1; break;
                case 25: return 1; break;
                case 26: return 1; break;
                case 27: return 2; break;
                case 28: return 2; break;
                case 29: return 2; break;
                case 30: return 1; break;
                case 31: return 0; break;
                case 32: return 1; break;
                case 33: return 1; break;
                case 34: return 2; break;
                case 35: return 1; break;
                case 36: return 1; break;
                case 37: return 1; break;
                case 38: return 1; break;
                case 39: return 1; break;
                case 40: return 1; break;
                default: return 0; break;
            }
        }
        else if(h == LEFT)
        {
            if(a == NORMAL)
                switch (rudimentID)
            {
                case 1: return 2; break;
                case 2: return 2; break;
                case 3: return 7; break;
                case 4: return 4; break;
                case 5: return 3; break;
                case 6: return 4; break;
                case 7: return 4; break;
                case 8: return 4; break;
                case 9: return 4; break;
                case 10: return 8; break;
                case 11: return 8; break;
                case 12: return 10; break;
                case 13: return 12; break;
                case 14: return 14; break;
                case 15: return 16; break;
                case 16: return 3; break;
                case 17: return 5; break;
                case 18: return 7; break;
                case 19: return 6; break;
                case 20: return 1; break;
                case 21: return 2; break;
                case 22: return 2; break;
                case 23: return 1; break;
                case 24: return 3; break;
                case 25: return 3; break;
                case 26: return 5; break;
                case 27: return 2; break;
                case 28: return 2; break;
                case 29: return 2; break;
                case 30: return 3; break;
                case 31: return 1; break;
                case 32: return 1; break;
                case 33: return 2; break;
                case 34: return 2; break;
                case 35: return 4; break;
                case 36: return 4; break;
                case 37: return 5; break;
                case 38: return 3; break;
                case 39: return 4; break;
                case 40: return 5; break;
                default: return 0; break;
            }
            else if(a == GHOST)
                switch (rudimentID)
            {
                case 1: return 0; break;
                case 2: return 0; break;
                case 3: return 0; break;
                case 4: return 2; break;
                case 5: return 0; break;
                case 6: return 0; break;
                case 7: return 0; break;
                case 8: return 0; break;
                case 9: return 0; break;
                case 10: return 0; break;
                case 11: return 0; break;
                case 12: return 0; break;
                case 13: return 0; break;
                case 14: return 0; break;
                case 15: return 0; break;
                case 16: return 0; break;
                case 17: return 0; break;
                case 18: return 0; break;
                case 19: return 0; break;
                case 20: return 1; break;
                case 21: return 1; break;
                case 22: return 2; break;
                case 23: return 2; break;
                case 24: return 1; break;
                case 25: return 1; break;
                case 26: return 1; break;
                case 27: return 2; break;
                case 28: return 2; break;
                case 29: return 2; break;
                case 30: return 1; break;
                case 31: return 2; break;
                case 32: return 2; break;
                case 33: return 4; break;
                case 34: return 4; break;
                case 35: return 0; break;
                case 36: return 2; break;
                case 37: return 4; break;
                case 38: return 2; break;
                case 39: return 4; break;
                case 40: return 6; break;
                default: return 0; break;
            }
            else if(a == ACCENT)
                switch (rudimentID)
            {
                case 1: return 0; break;
                case 2: return 0; break;
                case 3: return 0; break;
                case 4: return 1; break;
                case 5: return 0; break;
                case 6: return 0; break;
                case 7: return 1; break;
                case 8: return 2; break;
                case 9: return 2; break;
                case 10: return 1; break;
                case 11: return 2; break;
                case 12: return 1; break;
                case 13: return 1; break;
                case 14: return 1; break;
                case 15: return 1; break;
                case 16: return 1; break;
                case 17: return 1; break;
                case 18: return 1; break;
                case 19: return 0; break;
                case 20: return 0; break;
                case 21: return 1; break;
                case 22: return 2; break;
                case 23: return 1; break;
                case 24: return 1; break;
                case 25: return 1; break;
                case 26: return 1; break;
                case 27: return 2; break;
                case 28: return 0; break;
                case 29: return 2; break;
                case 30: return 1; break;
                case 31: return 0; break;
                case 32: return 1; break;
                case 33: return 1; break;
                case 34: return 0; break;
                case 35: return 1; break;
                case 36: return 1; break;
                case 37: return 1; break;
                case 38: return 1; break;
                case 39: return 1; break;
                case 40: return 1; break;
                default: return 0; break;
            }
        }
        
        //should never by called
        return 0;
    }
    
//    const char* const ClickGenerator_Rudiments::getName(int32_t rudimentID) const
//    {
//        static const char* const names[] = {
//            "1. Single Stroke Roll",
//            "2. Single Stroke Four",
//            "3. Single Stroke Seven",
//            "4. Multiple Bounce Roll",
//            "5. Triple Stroke Roll",
//            "6. Double Stroke Open Roll",
//            "7. Five Stroke Roll",
//            "8. Six Stroke Roll",
//            "9. Seven Stroke Roll",
//            "10. Nine Stroke Roll",
//            "11. Ten Stroke Roll",
//            "12. Eleven Stroke Roll",
//            "13. Thirteen Stroke Roll",
//            "14. Fifteen Stroke Roll",
//            "15. Seventeen Stroke Roll",
//            "16. Single Paradiddle",
//            "17. Double Paradiddle",
//            "18. Triple Paradiddle",
//            "19. Single Paradiddle-Diddle",
//            "20. Flam",
//            "21. Flam Accent",
//            "22. Flam Tap",
//            "23. Flamacue",
//            "24. Flam Paradiddle",
//            "25. Single Flammed Mill",
//            "26. Flam Paradiddle-Diddle",
//            "27. Pataflafla",
//            "28. Swiss Army Triplet",
//            "29. Inverted Flam Tap",
//            "30. Flam Drag",
//            "31. Drag",
//            "32. Single Drag Tap",
//            "33. Double Drag Tap",
//            "34. Lesson 25",
//            "35. Single Dragdiddle",
//            "36. Drag Paradiddle #1",
//            "37. Drag Paradiddle #2",
//            "38. Single Ratamacue",
//            "39. Double Ratamacue",
//            "40. Triple Ratamacue"
//        };
//        
//        if(rudimentID >= 1 && rudimentID <= 40)
//            return names[rudimentID-1];
//        else
//            return NULL;
//    }
    
} //namespace libTheClick
