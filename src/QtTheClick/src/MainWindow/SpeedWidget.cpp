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

#include "MainWindow/SpeedWidget.h"

//debug
// #include <iostream>

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
SpeedWidget::SpeedWidget(QWidget *parent)
    : QWidget(parent)
{
    //create and initialize widgets
    this->bpmTextLabel = new QLabel( this );
    this->bpmTextLabel->setObjectName( QString::fromUtf8("bpmTextLabel") );
    QFont fontBpmTextLabel;
    fontBpmTextLabel.setPointSize(20);
    fontBpmTextLabel.setBold(true);
    fontBpmTextLabel.setWeight(75);
    fontBpmTextLabel.setKerning(true);
    this->bpmTextLabel->setFont(fontBpmTextLabel);
    this->bpmTextLabel->setScaledContents(false);
    this->bpmTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->bpmTextLabel->setText( QString::fromUtf8("BPM:") );

    this->bpmSpeedLabel = new QLabel( this );
    this->bpmSpeedLabel->setObjectName(QString::fromUtf8("bpmSpeedLabel"));
    QFont fontBpmSpeedLabel;
    fontBpmSpeedLabel.setPointSize(40);
//    fontBpmSpeedLabel.setPixelSize(40);
    fontBpmSpeedLabel.setBold(true);
    fontBpmSpeedLabel.setWeight(75);
    fontBpmSpeedLabel.setKerning(true);
    this->bpmSpeedLabel->setFont(fontBpmSpeedLabel);
    this->bpmSpeedLabel->setScaledContents(false);
    this->bpmSpeedLabel->setAlignment(Qt::AlignCenter);
    this->bpmSpeedLabel->setText( QString::fromUtf8("???") );

    this->beatTextLabel = new QLabel( this );
    this->beatTextLabel->setObjectName( QString::fromUtf8("beatTextLabel") );
    QFont fontBeatTextLabel;
    fontBeatTextLabel.setPointSize(20);
    fontBeatTextLabel.setBold(true);
    fontBeatTextLabel.setWeight(75);
    fontBeatTextLabel.setKerning(true);
    this->beatTextLabel->setFont(fontBeatTextLabel);
    this->beatTextLabel->setScaledContents(false);
    this->beatTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->beatTextLabel->setText( QString::fromUtf8("Beat:") );

    this->beatCountLabel = new QLabel( this );
    this->beatCountLabel->setObjectName(QString::fromUtf8("beatCountLabel"));
    QFont fontBeatCountLabel;
    fontBeatCountLabel.setPointSize(20);
    fontBeatCountLabel.setBold(true);
    fontBeatCountLabel.setWeight(75);
    fontBeatCountLabel.setKerning(true);
    this->beatCountLabel->setFont(fontBeatCountLabel);
    this->beatCountLabel->setScaledContents(false);
    this->beatCountLabel->setAlignment(Qt::AlignCenter);
    this->beatCountLabel->setText( QString::fromUtf8("0") );

    this->speedDial = new QtSvgDial( this );
    this->speedDial->setObjectName( QString::fromUtf8("speedDial") );
    this->speedDial->setSkin( QString::fromUtf8("speedDial") );
    this->speedDial->setNubSizeToRadiusRatio(0.3);

    this->m10Button = new QtSvgButton( this );
    this->m10Button->setObjectName( QString::fromUtf8("m10Button") );
    this->m10Button->setSkin( QString::fromUtf8("m10Button") );

    this->p10Button = new QtSvgButton( this );
    this->p10Button->setObjectName( QString::fromUtf8("p10Button") );
    this->p10Button->setSkin( QString::fromUtf8("p10Button") );

    this->m5Button = new QtSvgButton( this );
    this->m5Button->setObjectName( QString::fromUtf8("m5Button") );
    this->m5Button->setSkin( QString::fromUtf8("m5Button") );

    this->p5Button = new QtSvgButton( this );
    this->p5Button->setObjectName( QString::fromUtf8("p5Button") );
    this->p5Button->setSkin( QString::fromUtf8("p5Button") );

    this->m2Button = new QtSvgButton( this );
    this->m2Button->setObjectName( QString::fromUtf8("m2Button") );
    this->m2Button->setSkin( QString::fromUtf8("m2Button") );

    this->p2Button = new QtSvgButton( this );
    this->p2Button->setObjectName( QString::fromUtf8("p2Button") );
    this->p2Button->setSkin( QString::fromUtf8("p2Button") );

    this->m1Button = new QtSvgButton( this );
    this->m1Button->setObjectName( QString::fromUtf8("m1Button") );
    this->m1Button->setSkin( QString::fromUtf8("m1Button") );

    this->p1Button = new QtSvgButton( this );
    this->p1Button->setObjectName( QString::fromUtf8("p1Button") );
    this->p1Button->setSkin( QString::fromUtf8("p1Button") );

    this->tapButton = new QtSvgButton( this );
    this->tapButton->setObjectName( QString::fromUtf8("tapButton") );
    this->tapButton->setSkin( QString::fromUtf8("tapButton") );

    this->playToggleSwitch = new QtSvgToggleSwitch( this );
    this->playToggleSwitch->setObjectName( QString::fromUtf8("playToggleSwitch") );
    this->playToggleSwitch->setSkin( QString::fromUtf8("playToggleSwitch") );

    this->stopButton = new QtSvgButton( this );
    this->stopButton->setObjectName( QString::fromUtf8("stopButton") );
    this->stopButton->setSkin( QString::fromUtf8("stopButton") );
}

SpeedWidget::~SpeedWidget()
{
    // if(this->ControlHorizontalLayout != NULL)
    //     delete this->ControlHorizontalLayout;

    // if(this->playToggleSwitch != NULL)
    //     delete this->playToggleSwitch;

    // if(this->stopButton != NULL)
    //     delete this->stopButton;
}

//*****************************
//********** METHODS **********
//*****************************
void SpeedWidget::resizeEvent(QResizeEvent* event)
{
    //call methode of parent class
    QWidget::resizeEvent(event);

    //do general stuff
    int curHeight = 0;
    int newHeight = event->size().height();
    int newWidth = event->size().width();
    int heightSpace = newHeight * SPEEDWIDGET_HEIGHT_RATIO_SPACE;
    int heigtNextElement = 0;
    int widthNextElement = 0;
    QFont fontNextElement;

    //place widgets
    heigtNextElement = newHeight * SPEEDWIDGET_HEIGHT_RATIO_BPM;
    widthNextElement = newWidth * SPEEDWIDGET_WIDTH_RATIO_BPM;

    fontNextElement = this->bpmSpeedLabel->font();
    fontNextElement.setPixelSize(heigtNextElement);
    this->bpmSpeedLabel->setFont(fontNextElement);

    this->bpmTextLabel->setGeometry( QRect(0, curHeight, newWidth, heigtNextElement) );
    this->bpmSpeedLabel->setGeometry( QRect(newWidth-widthNextElement, curHeight, widthNextElement, heigtNextElement) );
    curHeight += heigtNextElement + heightSpace;

    heigtNextElement = newHeight * SPEEDWIDGET_HEIGHT_RATIO_BEATS;

    fontNextElement = this->beatTextLabel->font();
    fontNextElement.setPixelSize(heigtNextElement);
    this->bpmTextLabel->setFont(fontNextElement);
    this->beatTextLabel->setFont(fontNextElement);
    this->beatCountLabel->setFont(fontNextElement);

    this->beatTextLabel->setGeometry( QRect(0, curHeight, newWidth, heigtNextElement) );
    this->beatCountLabel->setGeometry( QRect(newWidth-widthNextElement, curHeight, widthNextElement, heigtNextElement) );
    curHeight += heigtNextElement + heightSpace;

    heigtNextElement = newHeight * SPEEDWIDGET_HEIGHT_RATIO_DIAL;
    this->speedDial->setGeometry( QRect(0, curHeight, heigtNextElement, heigtNextElement) );
    curHeight += heigtNextElement + heightSpace;

    heigtNextElement = newHeight * SPEEDWIDGET_HEIGHT_RATIO_BUTTONS;
    widthNextElement = newWidth * SPEEDWIDGET_WIDTH_RATIO_BUTTONS;
    this->m10Button->setGeometry( QRect(0, curHeight, widthNextElement, heigtNextElement) );
    this->p10Button->setGeometry( QRect(widthNextElement, curHeight, widthNextElement, heigtNextElement) );
    curHeight += heigtNextElement;

    this->m5Button->setGeometry( QRect(0, curHeight, widthNextElement, heigtNextElement) );
    this->p5Button->setGeometry( QRect(widthNextElement, curHeight, widthNextElement, heigtNextElement) );
    curHeight += heigtNextElement;

    this->m2Button->setGeometry( QRect(0, curHeight, widthNextElement, heigtNextElement) );
    this->p2Button->setGeometry( QRect(widthNextElement, curHeight, widthNextElement, heigtNextElement) );
    curHeight += heigtNextElement;

    this->m1Button->setGeometry( QRect(0, curHeight, widthNextElement, heigtNextElement) );
    this->p1Button->setGeometry( QRect(widthNextElement, curHeight, widthNextElement, heigtNextElement) );
    curHeight += heigtNextElement + heightSpace;

    this->tapButton->setGeometry( QRect(0, curHeight, newWidth, heigtNextElement) );
    curHeight += heigtNextElement;

    this->playToggleSwitch->setGeometry( QRect(0, curHeight, widthNextElement, heigtNextElement) );
    this->stopButton->setGeometry( QRect(widthNextElement, curHeight, widthNextElement, heigtNextElement) );
}

//*****************************
//********** SIGNALS **********
//*****************************


//*****************************
//*********** SLOTS ***********
//*****************************

