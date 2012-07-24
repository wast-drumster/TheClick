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

#include "libTheClick/Sound/Sound_Mono.h"
#include "libTheClick/definitions.h"

#include <samplerate.h>
#include <sndfile.h>
#include <stdexcept>
#include <cmath>

//DEBUG
#include <iostream>

namespace libTheClick
{

    //***************************************
    //********** (DE/CON)STRUCTORS **********
    //***************************************
    Sound_Mono::Sound_Mono(std::string& path)
    {
        Sound_Mono( path.c_str() );
    }
    
    Sound_Mono::Sound_Mono(const char *path)
    {
        //initialization
        this->soundBuffer = NULL;
        this->length = 0;
        
        //open file
        SNDFILE *infile;
        SF_INFO	sfinfo;
        
        infile = sf_open(path, SFM_READ, &sfinfo);
        
        //read file content
        if(infile != NULL)
        {
            if(sfinfo.channels == 1)
            {
                this->soundBuffer = new float[sfinfo.frames];
                
                //for(sf_count_t i = 0; i<sfinfo.frames; i++)
                this->length = sf_readf_float (infile, this->soundBuffer, sfinfo.frames);
                
                if(this->length != sfinfo.frames)
                {
                    //exception detected --> clean up object
                    delete this->soundBuffer;
                    this->soundBuffer = NULL;
                    this->length = 0;
                    
                    //close file
                    sf_close(infile);
                    
                    //throw exception
                    throw std::logic_error("File could not be read completely.");
                }
                
                //sample rate conversation
                if(sfinfo.samplerate != SAMPLE_RATE)
                {
                    SRC_DATA samplerateConvertCfg;
                    samplerateConvertCfg.data_in       = this->soundBuffer;
                    samplerateConvertCfg.input_frames  = sfinfo.frames;
                    samplerateConvertCfg.src_ratio     = (double)SAMPLE_RATE / (double)sfinfo.samplerate;
                    samplerateConvertCfg.output_frames = (double)this->length * samplerateConvertCfg.src_ratio + 0.5;
                    samplerateConvertCfg.data_out      = new float[samplerateConvertCfg.output_frames];
                    
                    if( src_simple(&samplerateConvertCfg, SRC_SINC_BEST_QUALITY, 1) != 0 )
                    {
                        sf_close(infile);
                        throw std::logic_error("Sampleratecould not be converted.");
                    }
                    
                    delete this->soundBuffer;
                    this->soundBuffer = samplerateConvertCfg.data_out;
                    this->length = samplerateConvertCfg.output_frames;
                }
            }
            else
            {
                sf_close(infile);
                throw std::logic_error("File has incorrect amount of channels.");
            }
        }
        else
        {
            throw std::logic_error("File could not be opened.");
        }
        
        //normalize soundBuffer
        this->normalize();
        
        //close file
        sf_close(infile);
    }
    
    Sound_Mono::Sound_Mono(int64_t length)
    {
        this->length = length;
        this->soundBuffer = new float[length];
        
        for(int64_t i = 0; i<length; i++)
            this->soundBuffer[i] = 0.0f;
    }
    
    Sound_Mono::Sound_Mono(const Sound_Mono& rhs)
    {
        this->length = rhs.length;
        this->soundBuffer = new float[rhs.length];
        
        //copy buffer
        for(int64_t i = 0; i<rhs.length; i++)
            this->soundBuffer[i] = rhs.soundBuffer[i];
    }

    Sound_Mono::~Sound_Mono()
    {
        if(this->soundBuffer != NULL)
        {
            delete this->soundBuffer;
            this->soundBuffer = NULL;
        }
    }
        
    //*****************************
    //********** METHODS **********
    //*****************************
    void Sound_Mono::normalize()
    {
        //find max value in sound buffer
        float maxValue = 0.0f;
        for(int64_t i = 0; i<this->length; i++)
        {
            if(fabs( this->soundBuffer[i] ) > maxValue)
                maxValue = fabs( this->soundBuffer[i] );
        }
        
        //normalize soundBuffer
        if(maxValue > 0.0f)
        {
            for(int64_t i = 0; i<this->length; i++)
            {
                this->soundBuffer[i] /= maxValue;
            }
        }
    }
    
    Sound_Interface* Sound_Mono::cloneWithVolume(float vol)
    {
        Sound_Interface* ret = new Sound_Mono( *this );
        
        //set volume
        float*  sb = ret->getSoundBufferMono();
        for(int64_t i = 0; i<this->length; i++)
            sb[i] *= vol;
        
        //return
        return ret;
    }
    
} //namespace libTheClick
