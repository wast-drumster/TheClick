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

#ifndef _CLICKGENERATOR_DUMMYBEATCOUNT_HEADER_
#define _CLICKGENERATOR_DUMMYBEATCOUNT_HEADER_

#include "libTheClick/Sound/Sound_Interface.h"
#include "libTheClick/ClickGenerator/ClickGenerator_Interface.h"
#include "libTheClick/definitions.h"
#include "libTheClick/types.h"

#include "boost/function.hpp"
#include "boost/thread.hpp"

#include <list>

namespace libTheClick
{
    struct beatCountCallbackStruct
    {
        int32_t beatCount;
        double timeStamp;
        boost::function<double(void)> timeFuncPointer;
    };
        
    class ClickGenerator_DummyBeatCount : public ClickGenerator_Interface
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            ClickGenerator_DummyBeatCount();
            virtual ~ClickGenerator_DummyBeatCount();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected:
            
        private:
            ClickConfiguration* clickConfiguration;
                    
            int64_t                  lastBeatTime;
            std::list<SoundElement*> soundElementList;
            bool                     soundElementGenerationHasStarted;
        
            boost::function<void (int)> beatCountCallbackFunction;
            boost::thread* beatCountCallbackThread;
            bool beatCountCallbackThreadShouldStop;
            std::list<beatCountCallbackStruct*> beatCountCallbackStructList;
            
        //********** METHODS **********
        public: 
            //implement ClickGenerator_Interface
            virtual void   reset();
            virtual void   setClickConfiguration(ClickConfiguration* cc);
            virtual ClickConfiguration* getClickConfiguration();
            virtual std::list<SoundElement*>* getSoundElementList(int64_t time);
            virtual void   cleanSoundElements();
            
            //own methods
            void setBeatCountCallbackFunction( boost::function<void (int)> funcPointer ) {this->beatCountCallbackFunction = funcPointer;}
            void playbackCallbackBeat(int32_t beatCount, double timeStamp, boost::function<double(void)> timeFuncPointer );
        
        protected: 
            
        private:
            void generateSoundElements(int64_t endTime);
            void beatCountCallbackWorkerFunction();
            
    }; //class ClickGenerator_DivisionSubdivision
        
} //namespace libTheClick

#endif // _CLICKGENERATOR_DUMMYBEATCOUNT_HEADER_
