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

#ifndef _LIB_THECLICK_DEFINITIONS_HEADER_
#define _LIB_THECLICK_DEFINITIONS_HEADER_

/*************************************/
/*              DEFINE               */
/*************************************/

//general
#define SAMPLE_RATE                      (44100)
//#define SAMPLE_RATE                      (48000)


//SoundStream
#define SOUNDSTREAM__RING_BUFFER_SIZE    0
#define SOUNDSTREAM__MIN_SAMPLES_AHEAD   (0.5*SAMPLE_RATE)

//ClickGenarator_DivisionSubdivision
#define DIVSUBDIV__MAX_DIVISIONS         (20)
#define DIVSUBDIV__MAX_SUBDIVISIONS      (20)

//SoundBase

//ClickController
#define CLICKCONTROLLER__GENERATE_NEW_FRAMES   (0.8*SOUNDSTREAM__RING_BUFFER_SIZE)


#endif // _LIB_THECLICK_DEFINITIONS_HEADER_
