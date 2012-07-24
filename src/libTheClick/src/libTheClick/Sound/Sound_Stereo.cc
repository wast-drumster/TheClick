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

#include "libTheClick/Sound/Sound_Stereo.h"
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
    Sound_Stereo::Sound_Stereo(std::string& path)
    {
        Sound_Stereo( path.c_str() );
    }
    
    Sound_Stereo::Sound_Stereo(const char *path)
    {
        //initialization
        this->soundBufferLeft = NULL;
        this->soundBufferRight = NULL;
        this->soundBufferMono = NULL;

        this->length = 0;
        
        //open file
        SNDFILE *infile;
        SF_INFO	sfinfo;
        
        infile = sf_open(path, SFM_READ, &sfinfo);
        
        //read file content
        if(infile != NULL)
        {
            if(sfinfo.channels == 2)
            {
                //create temporary sound buffer --> this buffer is splitted up subsequently
                float* soundBufferTemp = new float[ sfinfo.frames * 2 ];
                
                //read file
                int64_t readFrames = sf_readf_float(infile, soundBufferTemp, sfinfo.frames);
                this->length = sfinfo.frames;
                
                //check if file was read completely
                if(readFrames != sfinfo.frames)
                {
                    //exception detected --> clean up object
                    delete soundBufferTemp;
                    //this->soundBufferTemp = NULL;
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
                    samplerateConvertCfg.data_in       = soundBufferTemp;
                    samplerateConvertCfg.input_frames  = sfinfo.frames;
                    samplerateConvertCfg.src_ratio     = (double)SAMPLE_RATE / (double)sfinfo.samplerate;
                    samplerateConvertCfg.output_frames = 2 * (long)( (double)this->length * samplerateConvertCfg.src_ratio + 0.5 );
                    samplerateConvertCfg.data_out      = new float[samplerateConvertCfg.output_frames];
                    
                    if( src_simple(&samplerateConvertCfg, SRC_SINC_BEST_QUALITY, 1) != 0 )
                    {
                        delete soundBufferTemp;
                        sf_close(infile);
                        throw std::logic_error("Sampleratecould not be converted.");
                    }
                    
                    delete soundBufferTemp;
                    soundBufferTemp = samplerateConvertCfg.data_out;
                    this->length = samplerateConvertCfg.output_frames / 2;
                }
                
                //split up temporary sound buffer
                this->soundBufferLeft = new float[ this->length ];
                this->soundBufferRight = new float[ this->length ];
                for(int64_t i = 0; i < this->length; i++)
                {
                    this->soundBufferLeft[i] = soundBufferTemp[i*2];
                    this->soundBufferRight[i] = soundBufferTemp[i*2 + 1];
                }
                
                //clean up
                delete soundBufferTemp;
            }
            else
            {
                sf_close(infile);
                throw std::logic_error("File has incorrect amount of channels");
            }
        }
        else
        {
            throw std::logic_error("File could not be opened.");
        }
        
        //normalize soundBuffers
        this->normalize();
        
        //close file
        sf_close(infile);
    }
    
    Sound_Stereo::Sound_Stereo(int64_t length)
    {
        this->length = length;
        this->soundBufferLeft = new float[length];
        this->soundBufferRight = new float[length];
    }
    
    Sound_Stereo::Sound_Stereo(const Sound_Stereo& rhs)
    {
        this->length = rhs.length;
        
        //copy stereo buffers
        if(rhs.soundBufferLeft != NULL &&
           rhs.soundBufferRight != NULL)
        {
            this->soundBufferLeft  = new float[rhs.length];
            this->soundBufferRight = new float[rhs.length];
                    
            //copy buffers
            for(int64_t i = 0; i<rhs.length; i++)
            {
                this->soundBufferLeft[i] = rhs.soundBufferLeft[i];
                this->soundBufferRight[i] = rhs.soundBufferRight[i];
            }
        }
        else
        {
            this->soundBufferLeft  = NULL;
            this->soundBufferRight = NULL;
        }
        
        //copy mono buffer
        if(rhs.soundBufferMono != NULL)
        {
            this->soundBufferMono  = new float[rhs.length];
            
            //copy buffers
            for(int64_t i = 0; i<rhs.length; i++)
            {
                this->soundBufferMono[i] = rhs.soundBufferMono[i];
            }
        }
        else
        {
            this->soundBufferMono = NULL;
        }
    }

    Sound_Stereo::~Sound_Stereo()
    {
        if(this->soundBufferLeft != NULL)
        {
            delete this->soundBufferLeft;
            this->soundBufferLeft = NULL;
        }
        
        if(this->soundBufferRight != NULL)
        {
            delete this->soundBufferRight;
            this->soundBufferRight = NULL;
        }
        
        if(this->soundBufferMono != NULL)
        {
            delete this->soundBufferMono;
            this->soundBufferMono = NULL;
        }
    }
        
    //*****************************
    //********** METHODS **********
    //*****************************
//    float* Sound_Stereo::getSoundBufferLeft()
//    {
//        return this->soundBufferLeft;
//    }
    
//    float* Sound_Stereo::getSoundBufferRight()
//    {
//        return this->soundBufferRight;
//    }
    
    float* Sound_Stereo::getSoundBufferMono()
    {
        //generate sound buffer if required
        if(this->soundBufferMono == NULL)
        {
            this->soundBufferMono = new float[ this->length ];
            
            for(int64_t i = 0; i < this->length; i++)
            {
                this->soundBufferMono[i] = this->soundBufferLeft[i] + this->soundBufferRight[i];
            }
        }
        
        //return sound buffer
        return this->soundBufferMono;
    }
        
    void Sound_Stereo::normalize()
    {
        //find max value in sound buffer
        float maxValue = 0.0f;
        for(int64_t i = 0; i<this->length; i++)
        {
            if(fabs( this->soundBufferLeft[i] ) > maxValue)
                maxValue = fabs( this->soundBufferLeft[i] );
            
            if(fabs( this->soundBufferRight[i] ) > maxValue)
                maxValue = fabs( this->soundBufferRight[i] );
        }
        
        //normalize soundBuffer
        if(maxValue > 0.0f)
        {
            for(int64_t i = 0; i<this->length; i++)
            {
                this->soundBufferLeft[i] /= maxValue;
                this->soundBufferRight[i] /= maxValue;
            }
        }
        
        //delete soundBufferMono if necessary
        if(this->soundBufferMono != NULL)
        {
            delete this->soundBufferMono;
            this->soundBufferMono = NULL;
        }
    }
    
    Sound_Interface* Sound_Stereo::cloneWithVolume(float vol)
    {
        Sound_Interface* ret = new Sound_Stereo( *this );
        
        //set volume
        float*  sbl = ret->getSoundBufferLeft();
        float*  sbr = ret->getSoundBufferRight();
        for(int64_t i = 0; i<this->length; i++)
        {
            sbl[i] *= vol;
            sbr[i] *= vol;
        }
        
        //return
        return ret;
    }

} //namespace libTheClick
