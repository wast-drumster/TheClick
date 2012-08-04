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

#ifndef _TYPES_HEADER_
#define _TYPES_HEADER_

/*************************************/
/*              DEFINE               */
/*************************************/

#include <stdint.h>


enum hand
{
    LEFT,
    RIGHT
};

enum accentuation
{
    GHOST,
    NORMAL,
    ACCENT
};

//! Identifies a ClickGenerator object in the ClickController
/*!
 * This value is returned if a ClickGenerator is added to the ClickController.
 * If a ClickGenerator should be removed from the ClickController, this value 
 * idetifies the ClickController. 
 */
typedef int32_t clickgen_id;

//! Identifies a drumkit in a SoundBase object
/*!
 * The ID drumkit_id is returned when a drumkit is loaded.
 */
typedef int32_t drumkit_id;

//! Identifies a instrument of a drumkit
/*!
 * This value has to be given if a drumkit object should return a SoundElement.
 */
typedef int32_t instrument_id;


#endif // _TYPES_HEADER_
