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

#ifndef _SOUNDELEMENT_HEADER_
#define _SOUNDELEMENT_HEADER_

#include "libTheClick/Sound/Sound_Interface.h"
#include "libTheClick/types.h"

#include "boost/shared_ptr.hpp"
#include "boost/function.hpp"

#include <string>

namespace libTheClick
{
    typedef boost::shared_ptr<Sound_Interface> SoundInterfaceShrPtr;    
    
    class SoundElement
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            SoundElement(drumkit_id drumKitID, instrument_id instrumentID, std::string& path, float volume);
            SoundElement(drumkit_id drumKitID, instrument_id instrumentID, const char *path, float volume);
            SoundElement(drumkit_id drumKitID, instrument_id instrumentID, Sound_Interface* sound, float volume);
            SoundElement(const SoundElement& se);
            virtual ~SoundElement();
        
        private:
            
        //********** ATTRIBUTES **********
        public:
            //! Indicates point in time where sound should be played.
            int64_t time;
            
            drumkit_id drumKitID;
            instrument_id instrumentID;
        
            //! playback callback attribute
            /*!
             * This attribute contains the point to the playback
             * callback function.
             */
            boost::function<void (double, boost::function<double(void)> )> playbackCallbackFunction;
            
        protected: 
            
        private:
            //! shared pointer which holds the Sound object
            /*!
             * The Sound object hold by this shared pointer contains
             * the sound which should be played. The content of the
             * Sound object should never be modified. For all volume
             * modifications, the multiplayVolumeWith methode should
             * be used.
             */
            SoundInterfaceShrPtr  soundShrPtr;
        
            //! Stores the volume for the playback of the sound.
            /*
             * This value is not already applied to the sound stored
             * at the sound pointer. So, it has to be applied at
             * playback time.
             */
            float volume;
            
        //********** METHODS **********
        public:
            SoundElement* cloneAndSetTime(int64_t time);
            SoundElement* clone();
            inline Sound_Interface* getSound() const {return this->soundShrPtr.get();}
            inline void  multiplayVolumeWith(float gain) {this->volume *= gain;}
            inline float getVolume() {return this->volume;}
            inline bool soundElementIsUnique() {return this->soundShrPtr.unique();}
        
            //! set methode for playback callback function
            /*
             * With this function, a callback function could be defined.
             * This callback function should be called, when the point
             * in time for the SoundElements's playback is clear. 
             */
            void setPlaybackCallback( boost::function<void (double, boost::function<double(void)> )> funcPointer ) {this->playbackCallbackFunction = funcPointer;}
            
            //! call methode for playback callback function
            /*!
             * This function should be called, when the
             * point in time for the SoundElement's playback is clear.
             * The first parameter contains the point in time for its
             * playback. The second parameter contains a point to a
             * variable which contains the current time.
             */
            void callPlaybackCallback(double timeStamp, boost::function<double(void)> timeFuncPointer);
            
        
        protected: 
            
        private:
            
            
    }; //class SoundElement
        
} //namespace libTheClick

#endif // _SOUNDELEMENT_HEADER_
