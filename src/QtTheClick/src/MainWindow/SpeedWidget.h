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

#ifndef SPEEDWIDGET_H
#define SPEEDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDateTime>

#include "widgets/svgtoggleswitch/qtsvgtoggleswitch.h"
#include "widgets/svgdial/qtsvgdial.h"
#include "widgets/svgbutton/qtsvgbutton.h"
#include "libTheClick/libTheClick.h"

#include <list>

#define SPEEDWIDGET_HEIGHT_WIDTH_RATIO          (560.0/140.0)
#define SPEEDWIDGET_HEIGHT_RATIO_SPACE          (0.01)
#define SPEEDWIDGET_HEIGHT_RATIO_BPM            (0.08)
#define SPEEDWIDGET_WIDTH_RATIO_BPM             (0.7)
#define SPEEDWIDGET_HEIGHT_RATIO_BEATS          (0.03)
#define SPEEDWIDGET_HEIGHT_RATIO_DIAL           (1.0/SPEEDWIDGET_HEIGHT_WIDTH_RATIO)
//#define SPEEDWIDGET_HEIGHT_RATIO_BUTTONS        (0.09)
#define SPEEDWIDGET_HEIGHT_RATIO_BUTTONS        (0.0943)
#define SPEEDWIDGET_WIDTH_RATIO_BUTTONS         (0.5)

class SpeedWidget : public QWidget
{
    Q_OBJECT
    
    //********** (DE/CON)STRUCTORS **********
    public:
        SpeedWidget(libTheClick::ClickController* clickController, QWidget *parent = 0);
        ~SpeedWidget();

    private:

    //********** ATTRIBUTES **********
    public: 
        //GUI elements
        QtSvgDial*         speedDial;

        QLabel*            bpmTextLabel;
        QLabel*            bpmSpeedLabel;
        QLabel*            beatTextLabel;
        QLabel*            beatCountLabel;

        QtSvgButton*       m10Button;
        QtSvgButton*       p10Button;
        QtSvgButton*       m5Button;
        QtSvgButton*       p5Button;
        QtSvgButton*       m2Button;
        QtSvgButton*       p2Button;
        QtSvgButton*       m1Button;
        QtSvgButton*       p1Button;

        QtSvgButton*       tapButton;

        QtSvgToggleSwitch* playToggleSwitch;
        QtSvgButton*       stopButton;

        //libTheClick stuff
        libTheClick::ClickController*                    clickController;
        libTheClick::ClickGenerator_DummyBeatCount*      cgDummyBeatCount;

        //own attributes
        std::list<QDateTime>tapList;

    protected: 
        
    private:
        
    //********** METHODS **********
    public: 
        //overload QWidget
        virtual int heightForWidth (int w) const {return SPEEDWIDGET_HEIGHT_WIDTH_RATIO * w;}
        void resizeEvent(QResizeEvent* event);

        //own stuff
        void theClickBeatsCallBack(int beats);
        
    protected: 
        
    private:

    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:
        void speedPlus10();
        void speedPlus05();
        void speedPlus02();
        void speedPlus01();
        void speedMinus10();
        void speedMinus05();
        void speedMinus02();
        void speedMinus01();
        void speedDialValueChanged(int value);

        void startButtonSlot();
        void stopButtonSlot();
        void tapButtonSlot();


};

#endif // SPEEDWIDGET_H
