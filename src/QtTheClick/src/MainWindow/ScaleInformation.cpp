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

#include "MainWindow/ScaleInformation.h"

//debug
// #include <iostream>

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
ScaleInformation::ScaleInformation()
{
    this->mainWindowWidth = 100;
    this->mainWindowHeight = 100;
}

ScaleInformation::~ScaleInformation()
{

}

//*****************************
//********** METHODS **********
//*****************************
ScaleInformation* ScaleInformation::getInstance()
{
    static ScaleInformation theInstance;
    return &theInstance;
}



int ScaleInformation::getHeightDialWithButtons() const
{
    return this->mainWindowHeight / SCALEINFORMATION_HEIGHT_RATIO_DIALWITHBUTTONS;
}

int ScaleInformation::getWidthDialWithButtons() const
{
    return this->mainWindowHeight / (double)SCALEINFORMATION_HEIGHT_RATIO_DIALWITHBUTTONS * (double)SCALEINFORMATION_WIDTH_HEIGHT_RATIO_DIALWITHBUTTONS;
}

int ScaleInformation::getWidthDialWithButtonsForMainWindowHeight(int h) const
{
    return h / (double)SCALEINFORMATION_HEIGHT_RATIO_DIALWITHBUTTONS * (double)SCALEINFORMATION_WIDTH_HEIGHT_RATIO_DIALWITHBUTTONS;
}



int ScaleInformation::getHeightMuteToggleSwitch() const
{
    return this->mainWindowHeight / SCALEINFORMATION_HEIGHT_RATIO_MUTESWITCH;
}

int ScaleInformation::getWidthMuteToggleSwitch() const
{
    return this->mainWindowHeight / (double)SCALEINFORMATION_HEIGHT_RATIO_MUTESWITCH * (double)SCALEINFORMATION_WIDTH_HEIGHT_RATIO_MUTESWITCH;
}

int ScaleInformation::getWidthMuteToggleSwitchForMainWindowHeight(int h) const
{
    return h / (double)SCALEINFORMATION_HEIGHT_RATIO_MUTESWITCH * (double)SCALEINFORMATION_WIDTH_HEIGHT_RATIO_MUTESWITCH;
}



int ScaleInformation::getPixelSizeNormalText() const
{
    return this->mainWindowHeight / SCALEINFORMATION_HEIGHT_RATIO_PIXELSIZENORMALTEXT;
}
