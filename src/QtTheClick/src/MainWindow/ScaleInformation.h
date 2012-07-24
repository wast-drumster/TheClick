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

#ifndef SCALEINFORMATION_H
#define SCALEINFORMATION_H

#include <QSize>

#define SCALEINFORMATION_HEIGHT_RATIO_DIALWITHBUTTONS         (500.0/22.0)
#define SCALEINFORMATION_WIDTH_HEIGHT_RATIO_DIALWITHBUTTONS   (90.0/22.0)
#define SCALEINFORMATION_HEIGHT_RATIO_PIXELSIZENORMALTEXT     (500.0/10.0)

class ScaleInformation
{
    //********** (DE/CON)STRUCTORS **********
    public:

    private: //singleton pattern
        ScaleInformation();
        virtual ~ScaleInformation();

    //********** ATTRIBUTES **********
    public:

    protected: 
        
    private:
        int mainWindowWidth;
        int mainWindowHeight;
        
    //********** METHODS **********
    public: 
        static ScaleInformation* getInstance();

        void setMainWindowWidth(int w) {this->mainWindowWidth = w;}
        void setMainWindowHeight(int h) {this->mainWindowHeight = h;}
        void setMainWindowSize(const QSize& s) {this->mainWindowWidth = s.width(); this->mainWindowHeight = s.height();}
        
        int getHeightDialWithButtons() const;
        int getWidthDialWithButtons() const;
        int getWidthDialWithButtonsForMainWindowHeight(int h) const;

        int getPixelSizeNormalText() const;

    protected: 
        
    private:


};

#endif // SCALEINFORMATION_H
