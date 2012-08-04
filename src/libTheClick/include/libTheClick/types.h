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


typedef int32_t clickgen_id;
typedef int32_t drumkit_id;
typedef int32_t instrument_id;


#endif // _TYPES_HEADER_
