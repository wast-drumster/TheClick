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

#ifndef ClICKGENERATORDIVISIONWIDGET_H
#define ClICKGENERATORDIVISIONWIDGET_H

#include "MainWindow/ClickGeneratorTab/ClickGeneratorAbstractWidget.h"
#include "widgets/svgdialwithbuttons/qtsvgdialwithbuttons.h"
#include "widgets/svgtoggleswitch/qtsvgtoggleswitch.h"
#include "widgets/svgslider/qtsvgslider.h"
#include <QWidget>
#include <QLabel>


#define DISTANCE_X_LEFT        (10)
#define DISTANCE_X_RIGHT       (10)
#define DISTANCE_Y_TOP         (10)
#define DISTANCE_Y_BOTTOM      (10)
#define SPACE_X                (5)
#define SPACE_Y                (5)

#define CLICKGEN_DISABLED_VALUE  (-1)

class ClickGeneratorDivisionWidget : public ClickGeneratorAbstractWidget
{
    Q_OBJECT

    //********** PRELIMINARY **********
    public:
//        enum SoundID
//        {
//            DIV_01,
//        };
    
    //********** (DE/CON)STRUCTORS **********
    public:
        ClickGeneratorDivisionWidget(libTheClick::ClickController* clickController, QWidget *parent = 0);
        virtual ~ClickGeneratorDivisionWidget();

    private:

    //********** ATTRIBUTES **********
    public: 
        //GUI elements
        QtSvgDialWithButtons* divisionLevelControl[DIVSUBDIV__MAX_DIVISIONS];
        QtSvgDialWithButtons* subdivisionLevelControl[DIVSUBDIV__MAX_SUBDIVISIONS];
        QtSvgDialWithButtons* amountDivisions;
        QtSvgDialWithButtons* amountSubdivisions;
        QtSvgToggleSwitch*    muteToggleSwitch;
        QtSvgSlider*          volumeSlider;
        QLabel*               divisionTextLabel;
        QLabel*               subdivisionTextLabel;

        //libTheClick stuff
        libTheClick::ClickController*                    clickController;
        libTheClick::ClickGenerator_DivisionSubdivision* clickGenerator;
        clickgen_id                                      clickgenID;

        drumkit_id    divDivDrumKitIDArray[DIVSUBDIV__MAX_DIVISIONS];
        instrument_id divDivInstrumentIDArray[DIVSUBDIV__MAX_DIVISIONS];
        drumkit_id    divSubdivDrumKitIDArray[DIVSUBDIV__MAX_SUBDIVISIONS];
        instrument_id divSubdivInstrumentIDArray[DIVSUBDIV__MAX_SUBDIVISIONS];
        
    protected: 
        
    private:
        
    //********** METHODS **********
    public:
        //overload QWidget
        virtual QSize sizeHint () const;
        virtual int heightForWidth (int w) const;

        //overload ClickGeneratorAbstractWidget
        virtual int getMinimimWidthForMainWindowHeight(int h) const;
        virtual QList<XToXAssociationAbstractWidget*>* XToXAssociationWidgetFactory();
        virtual void setSoundConfiguration(clickgensound_id cgsID, drumkit_id dkID, instrument_id instrumentID);

        //own stuff
        libTheClick::ClickGenerator_DivisionSubdivision* getClickGenerator() {return this->clickGenerator;}
        
    protected: 
        
    private:
        void theClickDivisionCallBack(int division, int subdivision);

    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:
        //overload QWidget
        virtual void resizeEvent ( QResizeEvent * event );

        //own stuff
        void amountDivisionsChanged(int value);
        void amountSubdivisionsChanged(int value);
        void levelChanged(int);
        void volumeChanged(int);
        void muteSwitch();

};

#endif // ClICKGENERATORDIVISIONWIDGET_H
