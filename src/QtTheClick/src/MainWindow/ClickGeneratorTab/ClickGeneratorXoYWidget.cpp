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

#include "MainWindow/ClickGeneratorTab/ClickGeneratorXoYWidget.h"
#include "MainWindow/SoundConfigurationTab/ClickGeneratorSoundWidget.h"
#include "MainWindow/ScaleInformation.h"

#include "boost/bind.hpp"

//debug
// #include <iostream>

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
ClickGeneratorXoYWidget::ClickGeneratorXoYWidget(libTheClick::ClickController* clickController, QWidget *parent)
    : ClickGeneratorAbstractWidget(parent),
      clickController(clickController)
{
    //create and initialize widgets
    this->xTextLabel = new QLabel( this );
    this->xTextLabel->setObjectName( QString::fromUtf8("xTextLabel") );
    QFont fontXTextLabel;
    fontXTextLabel.setPointSize(10);
    fontXTextLabel.setBold(true);
    fontXTextLabel.setWeight(75);
    fontXTextLabel.setKerning(true);
    this->xTextLabel->setFont(fontXTextLabel);
    this->xTextLabel->setScaledContents(false);
    this->xTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->xTextLabel->setText( QString::fromUtf8("X:") );

    this->amountX = new QtSvgDialWithButtons( this );
    this->amountX->setDialSkin( QString::fromUtf8("levelDial") );
    this->amountX->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->amountX->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->amountX->setMinimum(1);
    this->amountX->setMaximum(20);
    this->amountX->dial->setNubSizeToRadiusRatio(0.6);
    this->amountX->dial->setNubRadius(0.5);
    this->amountX->setValue(3);
    connect(this->amountX, SIGNAL(valueChanged(int)), this, SLOT(amountXoYChanged(int)));

    this->levelX = new QtSvgDialWithButtons( this );
    this->levelX->setDialSkin( QString::fromUtf8("levelDial") );
    this->levelX->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->levelX->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->levelX->setMinimum(1);
    this->levelX->setMaximum(100);
    this->levelX->dial->setNubSizeToRadiusRatio(0.6);
    this->levelX->dial->setNubRadius(0.5);
    this->levelX->setValue(50);
    connect(this->levelX, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));

    this->yTextLabel = new QLabel( this );
    this->yTextLabel->setObjectName( QString::fromUtf8("yTextLabel") );
    QFont fontYTextLabel;
    fontYTextLabel.setPointSize(10);
    fontYTextLabel.setBold(true);
    fontYTextLabel.setWeight(75);
    fontYTextLabel.setKerning(true);
    this->yTextLabel->setFont(fontYTextLabel);
    this->yTextLabel->setScaledContents(false);
    this->yTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->yTextLabel->setText( QString::fromUtf8("Y:") );

    this->amountY = new QtSvgDialWithButtons( this );
    this->amountY->setDialSkin( QString::fromUtf8("levelDial") );
    this->amountY->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->amountY->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->amountY->setMinimum(1);
    this->amountY->setMaximum(20);
    this->amountY->dial->setNubSizeToRadiusRatio(0.6);
    this->amountY->dial->setNubRadius(0.5);
    this->amountY->setValue(4);
    connect(this->amountY, SIGNAL(valueChanged(int)), this, SLOT(amountXoYChanged(int)));

    this->levelY = new QtSvgDialWithButtons( this );
    this->levelY->setDialSkin( QString::fromUtf8("levelDial") );
    this->levelY->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->levelY->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->levelY->setMinimum(1);
    this->levelY->setMaximum(100);
    this->levelY->dial->setNubSizeToRadiusRatio(0.6);
    this->levelY->dial->setNubRadius(0.5);
    this->levelY->setValue(20);
    connect(this->levelY, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));

    this->xCountLabel = new QLabel( this );
    this->xCountLabel->setObjectName( QString::fromUtf8("xCountLabel") );
    QFont fontXCountLabel;
    fontXCountLabel.setPointSize(10);
    fontXCountLabel.setBold(true);
    fontXCountLabel.setWeight(75);
    fontXCountLabel.setKerning(true);
    this->xCountLabel->setFont(fontXCountLabel);
    this->xCountLabel->setScaledContents(false);
    this->xCountLabel->setAlignment(Qt::AlignLeading|Qt::AlignHCenter|Qt::AlignVCenter);
    this->xCountLabel->setText( QString::fromUtf8("") );

    this->volumeSlider = new QtSvgSlider( this );
    this->volumeSlider->setSkin( QString::fromUtf8("volumeSlider") );
    this->volumeSlider->setMinimum( 0 );
    this->volumeSlider->setMaximum( 100 );
    this->volumeSlider->setValue( 80 );
    connect(this->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(volumeChanged(int)));

    this->muteToggleSwitch = new QtSvgToggleSwitch( this );
    this->muteToggleSwitch->setSkin( QString::fromUtf8("muteToggleSwitch") );
    connect(this->muteToggleSwitch, SIGNAL(clicked()), this, SLOT(muteSwitch()));

    //initialize and configure stuff for libTheClick
    this->clickGenerator = new libTheClick::ClickGenerator_XoverY();
    this->xyXDrumKitID = 0;
    this->xyXInstrumentID = 1;
    this->xyYDrumKitID = 0;
    this->xyYInstrumentID = 1;

    this->clickGenerator->setX( this->amountX->value() );
    this->clickGenerator->setY( this->amountY->value() );
    this->levelChanged(0); //load SoundElements into clickgenerator
    this->clickGenerator->setXCountCallbackFunction( boost::bind( &ClickGeneratorXoYWidget::theClickXCallBack, &(*this) , _1) );

    //update valume
    this->clickgenID = CLICKGEN_DISABLED_VALUE;
    this->volumeChanged( this->volumeSlider->value() );
    this->muteToggleSwitch->setChecked(false);
    this->muteSwitch();
}

ClickGeneratorXoYWidget::~ClickGeneratorXoYWidget()
{

}

//*****************************
//********** METHODS **********
//*****************************
int ClickGeneratorXoYWidget::heightForWidth(int w) const
{
    int dialWithButtonsHeight = ScaleInformation::getInstance()->getHeightDialWithButtons();
//    int dialWithButtonsWidth = ScaleInformation::getInstance()->getWidthDialWithButtons();
    int muteHeight = ScaleInformation::getInstance()->getHeightMuteToggleSwitch();

    int curHeight = DISTANCE_Y_TOP;
    curHeight += dialWithButtonsHeight + SPACE_Y;
    curHeight += dialWithButtonsHeight + SPACE_Y;
    curHeight += muteHeight + SPACE_Y;
    curHeight += -SPACE_Y + DISTANCE_Y_BOTTOM;

    return curHeight;
}

QSize ClickGeneratorXoYWidget::sizeHint() const
{
    return QSize(this->parentWidget()->parentWidget()->geometry().width(), this->heightForWidth(this->parentWidget()->parentWidget()->geometry().width()));
}

int ClickGeneratorXoYWidget::getMinimumWidthForMainWindowHeight(int h) const
{
    return 4 * (ScaleInformation::getInstance()->getWidthDialWithButtonsForMainWindowHeight(h) + SPACE_X) + DISTANCE_X_LEFT + DISTANCE_X_RIGHT;
}

void ClickGeneratorXoYWidget::theClickXCallBack(int x)
{
    if(!this->muteToggleSwitch->isChecked())
    {
        this->xCountLabel->setText( QString::number(x) );
    }
}

QList<XToXAssociationAbstractWidget*>* ClickGeneratorXoYWidget::XToXAssociationWidgetFactory()
{
    QList<XToXAssociationAbstractWidget*>* ret = new QList<XToXAssociationAbstractWidget*>;
    ClickGeneratorSoundWidget* nextWidget;

    nextWidget = new ClickGeneratorSoundWidget(this, XOY_SOUNDID_X);
    nextWidget->setText( QString::fromUtf8("X") );
    ret->push_back( nextWidget );

    nextWidget = new ClickGeneratorSoundWidget(this, XOY_SOUNDID_Y);
    nextWidget->setText( QString::fromUtf8("Y") );
    ret->push_back( nextWidget );

    //return list
    return ret;
}

void ClickGeneratorXoYWidget::setSoundConfiguration(clickgensound_id cgsID, drumkit_id dkID, instrument_id instrumentID)
{
    //update configuration
    switch(cgsID)
    {
        case XOY_SOUNDID_X:
            this->xyXDrumKitID = dkID;
            this->xyXInstrumentID = instrumentID;
            break;
        case XOY_SOUNDID_Y:
            this->xyYDrumKitID = dkID;
            this->xyYInstrumentID = instrumentID;
            break;
    }

    //take over configuration
    this->levelChanged(0); //value is ignored
}

ClickGeneratorAbstractWidget::clickgensound_strings ClickGeneratorXoYWidget::getClickGenSoundStrings(clickgensound_id cgsID)
{
    clickgensound_strings ret;
    drumkit_id drumkitID = 0;
    instrument_id instrumentID = 0;

    switch(cgsID)
    {
        case XOY_SOUNDID_X:
            drumkitID = this->xyXDrumKitID;
            instrumentID = this->xyXInstrumentID;
            break;
        case XOY_SOUNDID_Y:
            drumkitID = this->xyYDrumKitID;
            instrumentID = this->xyYInstrumentID;
            break;
    }

    ret.drumkitName    = QString::fromStdString(
        this->clickController->getSoundBase()->getNameOfDrumKit(
            drumkitID
        )
    );
    ret.instrumentName = QString::fromStdString(
        this->clickController->getSoundBase()->getNameOfInstrument(
            drumkitID,
            instrumentID
        )
    );

    return ret;
}

void ClickGeneratorXoYWidget::setClickGenSoundStrings(clickgensound_id cgsID, clickgensound_strings cgsSt)
{
    drumkit_id    drumkitID    = this->clickController->getSoundBase()->getDrumKitID( cgsSt.drumkitName.toStdString() ) ;
    instrument_id instrumentID = this->clickController->getSoundBase()->getInstrumentID( cgsSt.drumkitName.toStdString(), cgsSt.instrumentName.toStdString() ) ;

    //update configuration
    switch(cgsID)
    {
        case XOY_SOUNDID_X:
            this->xyXDrumKitID = drumkitID;
            this->xyXInstrumentID = instrumentID;
            break;
        case XOY_SOUNDID_Y:
            this->xyYDrumKitID = drumkitID;
            this->xyYInstrumentID = instrumentID;
            break;
    }

    //take over configuration
    this->levelChanged(0); //value is ignored
}

//*****************************
//********** SIGNALS **********
//*****************************


//*****************************
//*********** SLOTS ***********
//*****************************
void ClickGeneratorXoYWidget::resizeEvent ( QResizeEvent * event )
{
    int curHeight = DISTANCE_Y_TOP;
    int dialWithButtonsHeight = ScaleInformation::getInstance()->getHeightDialWithButtons();
    int dialWithButtonsWidth = ScaleInformation::getInstance()->getWidthDialWithButtons();
    int muteHeight = ScaleInformation::getInstance()->getHeightMuteToggleSwitch();
    int muteWidth = ScaleInformation::getInstance()->getWidthMuteToggleSwitch();
    int textPixelSize = ScaleInformation::getInstance()->getPixelSizeNormalText();
    QFont fontNextElement;

    this->xTextLabel->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, this->size().width(), dialWithButtonsHeight) );
    fontNextElement = this->xTextLabel->font();
    fontNextElement.setPixelSize( textPixelSize );
    this->xTextLabel->setFont( fontNextElement );
    this->amountX->setGeometry( QRect(DISTANCE_X_LEFT + dialWithButtonsWidth + SPACE_X, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->levelX->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X) * 2, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->xCountLabel->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X) * 3, curHeight, dialWithButtonsWidth, dialWithButtonsHeight*2 + SPACE_Y) );
    fontNextElement.setPixelSize( dialWithButtonsHeight*2 );
    this->xCountLabel->setFont( fontNextElement );
    curHeight += dialWithButtonsHeight + SPACE_Y;

    this->yTextLabel->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, this->size().width(), dialWithButtonsHeight) );
    fontNextElement = this->yTextLabel->font();
    fontNextElement.setPixelSize( textPixelSize );
    this->yTextLabel->setFont( fontNextElement );
    this->amountY->setGeometry( QRect(DISTANCE_X_LEFT + dialWithButtonsWidth + SPACE_X, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->levelY->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X) * 2, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    curHeight += dialWithButtonsHeight + SPACE_Y;

    this->muteToggleSwitch->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, muteWidth, muteHeight) );
    this->volumeSlider->setGeometry( QRect(DISTANCE_X_LEFT + SPACE_X + muteWidth, curHeight + (muteHeight - dialWithButtonsHeight) / 2, this->size().width() - DISTANCE_X_LEFT - DISTANCE_X_RIGHT - SPACE_X - muteWidth, dialWithButtonsHeight) );

    update();
}

void ClickGeneratorXoYWidget::amountXoYChanged(int value)
{
    this->clickGenerator->setX( this->amountX->value() );
    this->clickGenerator->setY( this->amountY->value() );
}

void ClickGeneratorXoYWidget::levelChanged(int)
{
    this->clickGenerator->setXSoundElement(this->clickController->getSoundBase()->getSoundElement(
        this->xyXDrumKitID,
        this->xyXInstrumentID,
        (double)this->levelX->value() / (double)this->levelX->maximum())
    );

    this->clickGenerator->setYSoundElement(this->clickController->getSoundBase()->getSoundElement(
        this->xyYDrumKitID,
        this->xyYInstrumentID,
        (double)this->levelY->value() / (double)this->levelY->maximum())
    );
}

void ClickGeneratorXoYWidget::volumeChanged(int)
{
    if(this->clickgenID != CLICKGEN_DISABLED_VALUE)
        this->clickController->setVolumeforClickGenerator(this->clickgenID, (float)this->volumeSlider->value() / (float)this->volumeSlider->maximum());
}

void ClickGeneratorXoYWidget::muteSwitch()
{
    if(!this->muteToggleSwitch->isChecked())
    {
        //add click generator to click controller
        this->clickgenID = this->clickController->addClickGenerator( this->clickGenerator, (float)this->volumeSlider->value() / (float)this->volumeSlider->maximum() );
    }
    else
    {
        //remove click generator from click controller
        if(this->clickgenID != CLICKGEN_DISABLED_VALUE)
            this->clickController->removeClickGenerator( this->clickgenID );

        this->clickgenID = CLICKGEN_DISABLED_VALUE;

        //remove value from x-count label
        this->xCountLabel->setText("");
    }
}

