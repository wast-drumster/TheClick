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

#include "MainWindow/ClickGeneratorDivisionWidget.h"
#include "MainWindow/ScaleInformation.h"

#include "boost/bind.hpp"

//debug
// #include <iostream>

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
ClickGeneratorDivisionWidget::ClickGeneratorDivisionWidget(libTheClick::ClickController* clickController, QWidget *parent)
    : ClickGeneratorAbstractWidget(parent),
      clickController(clickController)
{
    //create and initialize widgets
    this->divisionTextLabel = new QLabel( this );
    this->divisionTextLabel->setObjectName( QString::fromUtf8("divisionTextLabel") );
    QFont fontdivisionTextLabel;
    fontdivisionTextLabel.setPointSize(10);
    fontdivisionTextLabel.setBold(true);
    fontdivisionTextLabel.setWeight(75);
    fontdivisionTextLabel.setKerning(true);
    this->divisionTextLabel->setFont(fontdivisionTextLabel);
    this->divisionTextLabel->setScaledContents(false);
    this->divisionTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->divisionTextLabel->setText( QString::fromUtf8("Divisions:") );

    this->amountDivisions = new QtSvgDialWithButtons( this );
    this->amountDivisions->setDialSkin( QString::fromUtf8("levelDial") );
    this->amountDivisions->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->amountDivisions->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->amountDivisions->setMinimum(1);
    this->amountDivisions->setMaximum(DIVSUBDIV__MAX_DIVISIONS);
    this->amountDivisions->dial->setNubSizeToRadiusRatio(0.6);
    this->amountDivisions->dial->setNubRadius(0.5);
    this->amountDivisions->setValue(4);
    connect(this->amountDivisions, SIGNAL(valueChanged(int)), this, SLOT(amountDivisionsChanged(int)));

    for(int i = 0; i<DIVSUBDIV__MAX_DIVISIONS; i++)
    {
        QtSvgDialWithButtons* dwb = new QtSvgDialWithButtons(this);
        this->divisionLevelControl[i] = dwb;
        dwb->setDialSkin( QString::fromUtf8("levelDial") );
        dwb->setButtonUpSkin( QString::fromUtf8("upButton") );
        dwb->setButtonDownSkin( QString::fromUtf8("downButton") );
        dwb->dial->setNubSizeToRadiusRatio(0.6);
        dwb->dial->setNubRadius(0.5);
        dwb->setMaximum(100);
        dwb->setMinimum(0);

        if(i == 0)
            dwb->setValue(100);
        else
            dwb->setValue(50);

        connect(dwb, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));
    }

    this->subdivisionTextLabel = new QLabel( this );
    this->subdivisionTextLabel->setObjectName( QString::fromUtf8("subdivisionTextLabel") );
    QFont fontsubdivisionTextLabel;
    fontsubdivisionTextLabel.setPointSize(10);
    fontsubdivisionTextLabel.setBold(true);
    fontsubdivisionTextLabel.setWeight(75);
    fontsubdivisionTextLabel.setKerning(true);
    this->subdivisionTextLabel->setFont(fontsubdivisionTextLabel);
    this->subdivisionTextLabel->setScaledContents(false);
    this->subdivisionTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->subdivisionTextLabel->setText( QString::fromUtf8("Subdivisions:") );

    this->amountSubdivisions = new QtSvgDialWithButtons( this );
    this->amountSubdivisions->setDialSkin( QString::fromUtf8("levelDial") );
    this->amountSubdivisions->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->amountSubdivisions->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->amountSubdivisions->setMinimum(1);
    this->amountSubdivisions->setMaximum(DIVSUBDIV__MAX_DIVISIONS);
    this->amountSubdivisions->dial->setNubSizeToRadiusRatio(0.6);
    this->amountSubdivisions->dial->setNubRadius(0.5);
    this->amountSubdivisions->setValue(2);
    connect(this->amountSubdivisions, SIGNAL(valueChanged(int)), this, SLOT(amountSubdivisionsChanged(int)));

    for(int i = 0; i<DIVSUBDIV__MAX_SUBDIVISIONS; i++)
    {
        QtSvgDialWithButtons* dwb = new QtSvgDialWithButtons(this);
        this->subdivisionLevelControl[i] = dwb;
        dwb->setDialSkin( QString::fromUtf8("levelDial") );
        dwb->setButtonUpSkin( QString::fromUtf8("upButton") );
        dwb->setButtonDownSkin( QString::fromUtf8("downButton") );
        dwb->dial->setNubSizeToRadiusRatio(0.6);
        dwb->dial->setNubRadius(0.5);
        dwb->setMaximum(100);
        dwb->setMinimum(0);
        dwb->setValue(20);
        connect(dwb, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));
    }

    this->volumeSlider = new QtSvgSlider( this );
    this->volumeSlider->setSkin( QString::fromUtf8("volumeSlider") );
    this->volumeSlider->setMinimum( 0 );
    this->volumeSlider->setMaximum( 100 );
    this->volumeSlider->setValue( 100 );
    connect(this->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(volumeChanged(int)));

    this->muteToggleSwitch = new QtSvgToggleSwitch( this );
    this->muteToggleSwitch->setSkin( QString::fromUtf8("muteToggleSwitch") );

    //initialize and configure stuff for libTheClick
    this->clickGenerator = new libTheClick::ClickGenerator_DivisionSubdivision();
    for(int i = 0; i < DIVSUBDIV__MAX_DIVISIONS; i++)
    {
        this->divDivDrumKitIDArray[i] = 0;
        this->divDivInstrumentIDArray[i] = 0;
    }

    for(int i = 0; i < DIVSUBDIV__MAX_SUBDIVISIONS; i++)
    {
        this->divSubdivDrumKitIDArray[i] = 0;
        this->divSubdivInstrumentIDArray[i] = 18;
    }

    this->clickGenerator->setAmountDivisions( this->amountDivisions->value() );
    this->clickGenerator->setAmountSubdivisions( this->amountSubdivisions->value() );
    this->levelChanged(0); //load SoundElements into clickgenerator
    this->clickGenerator->setDivisionCallbackFunction( boost::bind( &ClickGeneratorDivisionWidget::theClickDivisionCallBack, &(*this) , _1, _2) );
    this->clickgenID = this->clickController->addClickGenerator( this->clickGenerator, 1.0 );

    //update valume
    this->volumeChanged( this->volumeSlider->value() );
}

ClickGeneratorDivisionWidget::~ClickGeneratorDivisionWidget()
{

}

//*****************************
//********** METHODS **********
//*****************************
void ClickGeneratorDivisionWidget::theClickDivisionCallBack(int division, int subdivision)
{
    for(int i = 0; i<DIVSUBDIV__MAX_DIVISIONS; i++)
    {
        if(i == division)
            this->divisionLevelControl[i]->setShouldGlow(true);
        else
            this->divisionLevelControl[i]->setShouldGlow(false);
    }

    for(int i = 0; i<DIVSUBDIV__MAX_SUBDIVISIONS; i++)
    {
        if(i == subdivision)
            this->subdivisionLevelControl[i]->setShouldGlow(true);
        else
            this->subdivisionLevelControl[i]->setShouldGlow(false);
    }
}

//*****************************
//********** SIGNALS **********
//*****************************


//*****************************
//*********** SLOTS ***********
//*****************************
void ClickGeneratorDivisionWidget::resizeEvent ( QResizeEvent * event )
{
    //general stuff
    int curHeight = DISTANCE_Y_TOP;
    int dialWithButtonsHeight = ScaleInformation::getInstance()->getHeightDialWithButtons();
    int dialWithButtonsWidth = ScaleInformation::getInstance()->getWidthDialWithButtons();
    int muteHeight = ScaleInformation::getInstance()->getHeightMuteToggleSwitch();
    int muteWidth = ScaleInformation::getInstance()->getWidthMuteToggleSwitch();
    int textPixelSize = ScaleInformation::getInstance()->getPixelSizeNormalText();
    QFont fontNextElement;

    //elastic width
    int maxPerLine = (this->geometry().width() - DISTANCE_X_LEFT - DISTANCE_X_RIGHT) / (dialWithButtonsWidth - 1/*avoid to early break over*/ + SPACE_X);
    if(maxPerLine == 0) maxPerLine = 1;
    int freePixelPerLine = (this->geometry().width() - DISTANCE_X_LEFT - DISTANCE_X_RIGHT) - maxPerLine * (dialWithButtonsWidth + SPACE_X);
    if(freePixelPerLine < 0) freePixelPerLine = 0;
    double elasticWidth = (double)freePixelPerLine / (maxPerLine - 1);

    //place widgets
    this->divisionTextLabel->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, this->size().width(), dialWithButtonsHeight) );
    fontNextElement = this->divisionTextLabel->font();
    fontNextElement.setPixelSize( textPixelSize );
    this->divisionTextLabel->setFont( fontNextElement );
    this->amountDivisions->setGeometry( QRect(DISTANCE_X_LEFT + dialWithButtonsWidth + SPACE_X + elasticWidth, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    curHeight += dialWithButtonsHeight + SPACE_Y;

    {
        for(int i = 0; i<DIVSUBDIV__MAX_DIVISIONS; i++)
        {
            //place and show DialWithButtons
            if( (i / maxPerLine) <= ((this->amountDivisions->value()-1) / maxPerLine) )
            {
                this->divisionLevelControl[i]->setGeometry(
                    QRect(DISTANCE_X_LEFT + (i % maxPerLine) * (dialWithButtonsWidth + SPACE_X + elasticWidth),
                          curHeight + (i / maxPerLine) * (dialWithButtonsHeight + SPACE_Y),
                          dialWithButtonsWidth,
                          dialWithButtonsHeight)
                );
                this->divisionLevelControl[i]->setVisible(true);
            }
            else
            {
                this->divisionLevelControl[i]->setVisible(false);
            }

            //set not used DialWithButtons of the shown line to inactive
            if(i < this->amountDivisions->value())
                this->divisionLevelControl[i]->setIsInactive(false);
            else
                this->divisionLevelControl[i]->setIsInactive(true);
        }

        curHeight += (dialWithButtonsHeight + SPACE_Y) * ((this->amountDivisions->value()-1) / maxPerLine + 1);
    }

    this->subdivisionTextLabel->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, this->size().width(), dialWithButtonsHeight) );
    fontNextElement = this->subdivisionTextLabel->font();
    fontNextElement.setPixelSize( textPixelSize );
    this->subdivisionTextLabel->setFont( fontNextElement );
    this->amountSubdivisions->setGeometry( QRect(DISTANCE_X_LEFT + dialWithButtonsWidth + SPACE_X + elasticWidth, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    curHeight += dialWithButtonsHeight + SPACE_Y;

    {
        for(int i = 0; i<DIVSUBDIV__MAX_DIVISIONS; i++)
        {
            //place and show DialWithButtons
            if( (i / maxPerLine) <= ((this->amountSubdivisions->value()-1) / maxPerLine) )
            {
                this->subdivisionLevelControl[i]->setGeometry(
                    QRect(DISTANCE_X_LEFT + (i % maxPerLine) * (dialWithButtonsWidth + SPACE_X + elasticWidth),
                          curHeight + (i / maxPerLine) * (dialWithButtonsHeight + SPACE_Y),
                          dialWithButtonsWidth,
                          dialWithButtonsHeight)
                );
                this->subdivisionLevelControl[i]->setVisible(true);
            }
            else
            {
                this->subdivisionLevelControl[i]->setVisible(false);
            }

            //set not used DialWithButtons of the shown line to inactive
            if(i < this->amountSubdivisions->value())
                this->subdivisionLevelControl[i]->setIsInactive(false);
            else
                this->subdivisionLevelControl[i]->setIsInactive(true);
        }

        curHeight += (dialWithButtonsHeight + SPACE_Y) * ((this->amountSubdivisions->value()-1) / maxPerLine + 1);
    }

    this->muteToggleSwitch->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, muteWidth, muteHeight) );
    this->volumeSlider->setGeometry( QRect(DISTANCE_X_LEFT + SPACE_X + muteWidth, curHeight + (muteHeight - dialWithButtonsHeight) / 2, this->size().width() - DISTANCE_X_LEFT - DISTANCE_X_RIGHT - SPACE_X - muteWidth, dialWithButtonsHeight) );

    update();
}

void ClickGeneratorDivisionWidget::amountDivisionsChanged(int value)
{
    this->clickGenerator->setAmountDivisions(value);
    this->resizeEvent( NULL );
    emit shouldResize();
}

void ClickGeneratorDivisionWidget::amountSubdivisionsChanged(int value)
{
    this->clickGenerator->setAmountSubdivisions(value);
    this->resizeEvent( NULL );
    emit shouldResize();
}

void ClickGeneratorDivisionWidget::levelChanged(int)
{
    for(int i = 0; i<DIVSUBDIV__MAX_DIVISIONS; i++)
    {
        //configure ClickGenerator
        this->clickGenerator->setDivisionPattern(i, this->clickController->getSoundBase()->getSoundElement(
            this->divDivDrumKitIDArray[i],
            this->divDivInstrumentIDArray[i],
            (double)this->divisionLevelControl[i]->value() / (double)this->divisionLevelControl[i]->maximum())
        );
    }

    for(int i = 0; i<DIVSUBDIV__MAX_SUBDIVISIONS; i++)
    {
        //configure ClickGenerator
        this->clickGenerator->setSubdivisionPattern(i, this->clickController->getSoundBase()->getSoundElement(
            this->divSubdivDrumKitIDArray[i],
            this->divSubdivInstrumentIDArray[i],
            (double)this->subdivisionLevelControl[i]->value() / (double)this->subdivisionLevelControl[i]->maximum())
        );
    }
}

int ClickGeneratorDivisionWidget::heightForWidth(int w) const
{
    int dialWithButtonsHeight = ScaleInformation::getInstance()->getHeightDialWithButtons();
    int dialWithButtonsWidth = ScaleInformation::getInstance()->getWidthDialWithButtons();
    int muteHeight = ScaleInformation::getInstance()->getHeightMuteToggleSwitch();

    int maxPerLine = (w - DISTANCE_X_LEFT - DISTANCE_X_RIGHT) / (dialWithButtonsWidth - 1/*avoid to early break over*/ + SPACE_X);
    if(maxPerLine == 0) maxPerLine = 1;

    int curHeight = DISTANCE_Y_TOP;
    curHeight += dialWithButtonsHeight + SPACE_Y;
    curHeight += (dialWithButtonsHeight + SPACE_Y) * ((this->amountDivisions->value()-1) / maxPerLine + 1);
    curHeight += dialWithButtonsHeight + SPACE_Y;
    curHeight += (dialWithButtonsHeight + SPACE_Y) * ((this->amountSubdivisions->value()-1) / maxPerLine + 1);
    curHeight += muteHeight + SPACE_Y;
    curHeight += -SPACE_Y + DISTANCE_Y_BOTTOM;

    return curHeight;
}

QSize ClickGeneratorDivisionWidget::sizeHint() const
{
    return QSize(this->parentWidget()->parentWidget()->geometry().width(), this->heightForWidth(this->parentWidget()->parentWidget()->geometry().width()));
}

int ClickGeneratorDivisionWidget::getMinimimWidthForMainWindowHeight(int h) const
{
    return 3 * (ScaleInformation::getInstance()->getWidthDialWithButtonsForMainWindowHeight(h) + SPACE_X) + DISTANCE_X_LEFT + DISTANCE_X_RIGHT;
}

void ClickGeneratorDivisionWidget::volumeChanged(int)
{
    this->clickController->setVolumeforClickGenerator(this->clickgenID, (float)this->volumeSlider->value() / (float)this->volumeSlider->maximum());
}
