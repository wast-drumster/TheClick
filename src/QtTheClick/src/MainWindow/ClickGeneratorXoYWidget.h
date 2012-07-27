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

#ifndef ClICKGENERATORXOYWIDGET_H
#define ClICKGENERATORXOYWIDGET_H

#include "MainWindow/ClickGeneratorAbstractWidget.h"
#include "widgets/svgdialwithbuttons/qtsvgdialwithbuttons.h"
#include "widgets/svgtoggleswitch/qtsvgtoggleswitch.h"
#include "widgets/svgslider/qtsvgslider.h"
#include "libTheClick/libTheClick.h"
#include <QLabel>

#define DISTANCE_X_LEFT        (10)
#define DISTANCE_X_RIGHT       (10)
#define DISTANCE_Y_TOP         (10)
#define DISTANCE_Y_BOTTOM      (10)
#define SPACE_X                (5)
#define SPACE_Y                (5)

#define CLICKGEN_DISABLED_VALUE  (-1)

class ClickGeneratorXoYWidget : public ClickGeneratorAbstractWidget
{
    Q_OBJECT
    
    //********** (DE/CON)STRUCTORS **********
    public:
        ClickGeneratorXoYWidget(libTheClick::ClickController* clickController, QWidget *parent = 0);
        virtual ~ClickGeneratorXoYWidget();

    private:

    //********** ATTRIBUTES **********
    public: 
        //GUI elements
        QtSvgDialWithButtons* levelX;
        QtSvgDialWithButtons* levelY;
        QtSvgDialWithButtons* amountX;
        QtSvgDialWithButtons* amountY;
        QtSvgToggleSwitch*    muteToggleSwitch;
        QtSvgSlider*          volumeSlider;
        QLabel*               xTextLabel;
        QLabel*               yTextLabel;
        
        //libTheClick stuff
        libTheClick::ClickController*                    clickController;
        libTheClick::ClickGenerator_XoverY*              clickGenerator;
        clickgen_id                                      clickgenID;

        drumkit_id  xyXDrumKitID;
        int32_t     xyXInstrumentID;
        drumkit_id  xyYDrumKitID;
        int32_t     xyYInstrumentID;
        
    protected: 
        
    private:
        
    //********** METHODS **********
    public:
        //overload QWidget
        virtual QSize sizeHint () const;
        virtual int heightForWidth (int w) const;

        //overload ClickGeneratorAbstractWidget
        virtual int getMinimimWidthForMainWindowHeight(int h) const;

        //own stuff
        libTheClick::ClickGenerator_XoverY* getClickGenerator() {return this->clickGenerator;}
        
    protected: 
        
    private:
        
    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:
        //overload QWidget
        virtual void resizeEvent ( QResizeEvent * event );

        //own stuff
        void amountXoYChanged(int value);
        void levelChanged(int);
        void volumeChanged(int);
        void muteSwitch();


};

#endif // ClICKGENERATORXOYWIDGET_H
