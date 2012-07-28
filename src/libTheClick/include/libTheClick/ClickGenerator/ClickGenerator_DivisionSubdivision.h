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

#ifndef _CLICKGENERATOR_DIVISION_SUBDIVISION_HEADER_
#define _CLICKGENERATOR_DIVISION_SUBDIVISION_HEADER_

#include "libTheClick/Sound/Sound_Interface.h"
#include "libTheClick/ClickGenerator/ClickGenerator_Interface.h"
#include "libTheClick/definitions.h"
#include "libTheClick/types.h"

#include <list>

#include "boost/function.hpp"
#include "boost/thread.hpp"


namespace libTheClick
{
    struct divisionCallbackStruct
    {
        int32_t division;
        int32_t subdivision;
        double timeStamp;
        boost::function<double(void)> timeFuncPointer;
    };
        
    class ClickGenerator_DivisionSubdivision : public ClickGenerator_Interface
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            ClickGenerator_DivisionSubdivision();
            virtual ~ClickGenerator_DivisionSubdivision();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected:
            
        private:
            ClickConfiguration* clickConfiguration;
        
            int32_t amountDivisions;
            int32_t amountSubdivisions;
            
            SoundElement*            divisionPattern[DIVSUBDIV__MAX_DIVISIONS];
            SoundElement*            subdivisionPattern[DIVSUBDIV__MAX_SUBDIVISIONS];
            int64_t                  lastBeatTime;
            std::list<SoundElement*> soundElementList;
            bool                     soundElementGenerationHasStarted;
        
            boost::function<void (int, int)> divisionCallbackFunction;
            boost::thread* divisionCallbackThread;
            bool divisionCallbackThreadShouldStop;
            std::list<divisionCallbackStruct*> beatCountCallbackStructList;
        
        //********** METHODS **********
        public: 
            //implement ClickGenerator_Interface
            virtual void   reset();
            virtual void   setClickConfiguration(ClickConfiguration* cc);
            virtual ClickConfiguration* getClickConfiguration();
            virtual std::list<SoundElement*>* getSoundElementList(int64_t time);
            virtual void   cleanSoundElements();
            
            //own methods
            int32_t getAmountDivisions() const;
            int32_t getAmountSubdivisions() const;
            void    setAmountDivisions(int32_t value);
            void    setAmountSubdivisions(int32_t value);
            
            SoundElement* getDivisionPattern(int32_t pos) const;
            SoundElement* getSubdivisionPattern(int32_t pos) const;
            void          setDivisionPattern(int32_t pos, SoundElement* se);
            void          setSubdivisionPattern(int32_t pos, SoundElement* se);
        
            void setDivisionCallbackFunction( boost::function<void (int, int)> funcPointer ) {this->divisionCallbackFunction = funcPointer;}
            void playbackCallbackDevision(int32_t division, int32_t subdivision, double timeStamp, boost::function<double(void)> timeFuncPointer );

        
        protected: 
            
        private:
            void generateSoundElements(int64_t endTime);
            void divisionCallbackWorkerFunction();
            
    }; //class ClickGenerator_DivisionSubdivision
        
} //namespace libTheClick

#endif // _CLICKGENERATOR_DIVISION_SUBDIVISION_HEADER_
