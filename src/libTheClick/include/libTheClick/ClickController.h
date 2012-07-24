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

#ifndef _CLICKCONTROLLER_HEADER_
#define _CLICKCONTROLLER_HEADER_

//#include "libTheClick/Sound.h"

#include "portaudio.h"

#include "libTheClick/ClickGenerator/ClickGeneratorElement.h"
#include "libTheClick/ClickConfiguration.h"
#include "libTheClick/types.h"

#include "boost/thread.hpp"
#include "boost/function.hpp"

#include <map>
#include <list>

namespace libTheClick
{
        
    class ClickController
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            ClickController();
            virtual ~ClickController();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected: 
            
        private:
            //! Map of ClickGenerator pointerss
            /*!
             * This map contains several ClickGenerators
             * which represent differnt click types.
             */
            std::map<clickgen_id,ClickGeneratorElement*> clickGeneratorMap;
            
            //! ClickGenerator Identifier
            /*!
             * This count accumulates the calls of
             * addClickGenerator().
             */
            clickgen_id clickGenAddCounter;
            
            //! Portaudio stream
            /*!
             * This stream represents the sound output
             */
            PaStream* outPaStream;

            //! ClickConfiguration pointer
            /*!
             * This attribute holds the pointer to the 
             * ClickConfiguration which has to be used by all
             * ClickGenerator in clickGeneratorVector.
             */
            ClickConfiguration* clickConfiguration;
            
            //! list of SoundElementPointers
            /*!
             * This list is used to store all referenzes to
             * SoundElements whose playback was already started. 
             */
            std::list<SoundElement*> soundElementList;
                            
        //********** METHODS **********
        public:
            //! addClickGenerator method
            /*!
             * This function could be used to add ClickGenerators
             * to the ClickController. All ClickGenerators are
             * simultaniously used to generate the output sound.
             * The volume is applied at playback.
             */
            clickgen_id addClickGenerator(ClickGenerator_Interface* cg, float vol);
            
            //! setVolumeforClickGenerator method
            /*
             * This method could be used to modify the volumne
             * of the referenced ClickGenerator
             */
            void setVolumeforClickGenerator(clickgen_id id, float vol);
            
            //! removeClickGenerator method
            /*!
             * This function could be used to remove ClickGenerators
             * from the ClickController. All ClickGenerators are
             * simultaniously used to generate the output sound.
             * The ClickGenerator object is NOT delete!
             */
            void removeClickGenerator(clickgen_id id);
            
            //! start method
            /*!
             * This methode starts the audio output.
             */
            void start();

            //! stop method
            /*!
             * This methode stops the audio output. If the
             * ClickController is started again without 
             * calling the reset method, it starts at the
             * time where it was stoped.
             */
            void stop();

            //! reset method
            /*!
             * This methode resets the ClickController. If
             * the reset method is called after stop was 
             * called, a subsequent play will start from 
             * the beginning.
             */
            void reset();
        
            //! set beats per minute
            /*!
             * This methode reconfigures the ClickConfiguration
             * object and causes a refill of the ring buffer
             * in the SoundStream object.
             */
            void setBeatsPerMinute(int32_t bpm);
            
            //! get beats per minute
            /*!
             * This methode returns the BPM value from the
             * ClickConfiguration object.
             */
            inline const int32_t getBeatsPerMinute() const {return this->clickConfiguration->getBeatsPerMinute();}
            
            //! return sound base
            /*!
             * Tis methode returns the sound base from the
             * ClickConfiguration. This is necessary due to
             * be able to load the ClickGenerators with
             * Soundelements.
             */
            SoundBase* getSoundBase() const;
                    
        protected: 
            
        private:            
            //! call back methode for Portaudio
            /*!
             * This methode handles all OS's callbacks, and such,
             * copies the audio output frames from SoundStream 
             * to the OS.
             */
            static int paCallback(const void *inputBuffer, void *outputBuffer,
                                  unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo* timeInfo,
                                  PaStreamCallbackFlags statusFlags,
                                  void *userData );
        
    }; //class ClickController
        
} //namespace libTheClick

#endif // _CLICKCONTROLLER_HEADER_
