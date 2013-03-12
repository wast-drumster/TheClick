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

#ifndef _CLICKGENERATOR_RUDIMENTS_HEADER_
#define _CLICKGENERATOR_RUDIMENTS_HEADER_

#include "libTheClick/Sound/Sound_Interface.h"
#include "libTheClick/ClickGenerator/ClickGenerator_Interface.h"
#include "libTheClick/definitions.h"

#include "libTheClick/types.h"
#include <vector>

namespace libTheClick
{
        
    class ClickGenerator_Rudiments : public ClickGenerator_Interface
    {
        //********** (DE/CON)STRUCTORS **********
        public: 
            explicit ClickGenerator_Rudiments();
            virtual ~ClickGenerator_Rudiments();
        
        private:
            
        //********** ATTRIBUTES **********
        public: 
            
        protected:
            
        private:
            ClickConfiguration*      clickConfiguration;
        
            int32_t                  rudimentsID;
        
            SoundElement*            rNormalSoundElement;
            SoundElement*            rGhostSoundElement;
            SoundElement*            rAccentSoundElement;
            SoundElement*            lNormalSoundElement;
            SoundElement*            lGhostSoundElement;
            SoundElement*            lAccentSoundElement;
        
        
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
            int32_t getRudimentsID() const;
            void    setRudimentsID(int32_t value);
            
            SoundElement* getSoundElement(hand h, accentuation a) const;
            void          setSoundElement(hand h, accentuation a, SoundElement* se);
        
            static const char* const getName(int32_t rudimentID)
            {
                static const char* const names[] = {
                    "1. Single Stroke Roll",
                    "2. Single Stroke Four",
                    "3. Single Stroke Seven",
                    "4. Multiple Bounce Roll",
                    "5. Triple Stroke Roll",
                    "6. Double Stroke Open Roll",
                    "7. Five Stroke Roll",
                    "8. Six Stroke Roll",
                    "9. Seven Stroke Roll",
                    "10. Nine Stroke Roll",
                    "11. Ten Stroke Roll",
                    "12. Eleven Stroke Roll",
                    "13. Thirteen Stroke Roll",
                    "14. Fifteen Stroke Roll",
                    "15. Seventeen Stroke Roll",
                    "16. Single Paradiddle",
                    "17. Double Paradiddle",
                    "18. Triple Paradiddle",
                    "19. Single Paradiddle-Diddle",
                    "20. Flam",
                    "21. Flam Accent",
                    "22. Flam Tap",
                    "23. Flamacue",
                    "24. Flam Paradiddle",
                    "25. Single Flammed Mill",
                    "26. Flam Paradiddle-Diddle",
                    "27. Pataflafla",
                    "28. Swiss Army Triplet",
                    "29. Inverted Flam Tap",
                    "30. Flam Drag",
                    "31. Drag",
                    "32. Single Drag Tap",
                    "33. Double Drag Tap",
                    "34. Lesson 25",
                    "35. Single Dragdiddle",
                    "36. Drag Paradiddle #1",
                    "37. Drag Paradiddle #2",
                    "38. Single Ratamacue",
                    "39. Double Ratamacue",
                    "40. Triple Ratamacue"
                };
                
                if(rudimentID >= 1 && rudimentID <= 40)
                    return names[rudimentID-1];
                else
                    return NULL;
            }
        
        protected: 
            
        private:
            void    generateSoundElements(int64_t endTime);
            inline int32_t getRudimentLength(int32_t rudimentID) const;
            inline double* getRudimentTimeValues(hand h, accentuation a, int32_t rudimentID) const;
            inline int32_t getRudimentVectorLength(hand h, accentuation a, int32_t rudimentID) const;
            
    }; //class ClickGenerator_DivisionSubdivision
        
} //namespace libTheClick

#endif // _CLICKGENERATOR_RUDIMENTS_HEADER_
