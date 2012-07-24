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

#include "libTheClick/Sound/Sound_Interface.h"
#include "libTheClick/definitions.h"

#include "libTheClick/Sound/Sound_Mono.h"
#include "libTheClick/Sound/Sound_Stereo.h"

#include <sndfile.h>
#include <stdexcept>
#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************

        
    //*****************************
    //********** METHODS **********
    //*****************************
    Sound_Interface* Sound_Interface::loadSoundFromFile(std::string& path)
    {
        return Sound_Interface::loadSoundFromFile( path.c_str() );
    }
    
    Sound_Interface* Sound_Interface::loadSoundFromFile(const char *path)
    {
        Sound_Interface* ret = NULL;
        
        //open file
        SNDFILE *infile;
        SF_INFO	sfinfo;
        
        infile = sf_open(path, SFM_READ, &sfinfo);
        
        //close file
        sf_close(infile);
        
        //create appropriate Sound Object
        if(sfinfo.channels == 1)
        {
            ret = new Sound_Mono(path);
        }
        else if(sfinfo.channels == 2)
        {
            ret =  new Sound_Stereo(path);
        }
        else
        {
            throw std::logic_error("No appropriate Sound class available.");
        }
        
        //log output
        std::cout << "Sound loaded: " << path << std::endl;
        
        //return
        return ret;
    }
    
} //namespace libTheClick
