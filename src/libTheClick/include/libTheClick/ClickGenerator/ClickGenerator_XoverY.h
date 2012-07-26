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

#ifndef _CLICKGENERATOR_XOVERY_HEADER_
#define _CLICKGENERATOR_XOVERY_HEADER_

#include "libTheClick/Sound/Sound_Interface.h"
#include "libTheClick/ClickGenerator/ClickGenerator_Interface.h"
#include "libTheClick/definitions.h"

#include "libTheClick/types.h"
//#include <list>

namespace libTheClick
{
        
    class ClickGenerator_XoverY : public ClickGenerator_Interface
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            ClickGenerator_XoverY();
            virtual ~ClickGenerator_XoverY();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected:
            
        private:
            ClickConfiguration*      clickConfiguration;
        
            int32_t                  x;
            int32_t                  y;
        
            SoundElement*            xSoundElement;
            SoundElement*            ySoundElement;
            int64_t                  lastBeatTime;
            std::list<SoundElement*> soundElementList;
            bool                     soundElementGenerationHasStarted;
        
        //********** METHODS **********
        public: 
            //implement ClickGenerator_Interface
            virtual void   reset();
            virtual void   setClickConfiguration(ClickConfiguration* cc);
            virtual ClickConfiguration* getClickConfiguration();
            virtual std::list<SoundElement*>* getSoundElementList(int64_t time);
            virtual void   cleanSoundElements();
            
            //own methods
            int32_t getX() const;
            int32_t getY() const;
            void    setX(int32_t value);
            void    setY(int32_t value);
            
            SoundElement* getXSoundElement() const;
            SoundElement* getYSoundElement() const;
            void          setXSoundElement(SoundElement* se);
            void          setYSoundElement(SoundElement* se);
        
        protected: 
            
        private:
            void    generateSoundElements(int64_t endTime);
            
            
    }; //class ClickGenerator_DivisionSubdivision
        
} //namespace libTheClick

#endif // _CLICKGENERATOR_XOVERY_HEADER_
