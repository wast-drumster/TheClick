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

#include "MainWindow/ClickGeneratorTab/ClickGeneratorPASWidget.h"
#include "MainWindow/SoundConfigurationTab/ClickGeneratorSoundWidget.h"
#include "MainWindow/ScaleInformation.h"

//#include "boost/bind.hpp"

#include "libTheClick/types.h"

//debug
// #include <iostream>

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
ClickGeneratorPASWidget::ClickGeneratorPASWidget(libTheClick::ClickController* clickController, QWidget *parent)
    : ClickGeneratorAbstractWidget(parent),
      clickController(clickController)
{
    //create and initialize widgets
    this->rudimentTextLabel = new QLabel( this );
    this->rudimentTextLabel->setObjectName( QString::fromUtf8("rudimentTextLabel") );
    QFont fontRudimentTextLabel;
    fontRudimentTextLabel.setPointSize(10);
    fontRudimentTextLabel.setBold(true);
    fontRudimentTextLabel.setWeight(75);
    fontRudimentTextLabel.setKerning(true);
    this->rudimentTextLabel->setFont(fontRudimentTextLabel);
    this->rudimentTextLabel->setScaledContents(false);
    this->rudimentTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->rudimentTextLabel->setText( QString::fromUtf8("Rudiment:") );

    this->rudimentsComboBox = new QComboBox( this );
    QFont fontRudimentComboBox;
    fontRudimentComboBox.setPointSize(10);
    fontRudimentComboBox.setBold(true);
    fontRudimentComboBox.setWeight(75);
    this->rudimentsComboBox->setFont(fontRudimentComboBox);

    for(int32_t i = 1; i<=40; i++)
        this->rudimentsComboBox->addItem( QString::fromUtf8( libTheClick::ClickGenerator_Rudiments::getName(i) ) );

    connect(this->rudimentsComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(rudimentChanged(int)));

    this->accentTextLabel = new QLabel( this );
    this->accentTextLabel->setObjectName( QString::fromUtf8("accentTextLabel") );
    this->accentTextLabel->setScaledContents(false);
    this->accentTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignHCenter|Qt::AlignVCenter);
    this->accentTextLabel->setText( QString::fromUtf8("Accent") );

    this->normalTextLabel = new QLabel( this );
    this->normalTextLabel->setObjectName( QString::fromUtf8("normalTextLabel") );
    this->normalTextLabel->setScaledContents(false);
    this->normalTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignHCenter|Qt::AlignVCenter);
    this->normalTextLabel->setText( QString::fromUtf8("Normal") );

    this->ghostTextLabel = new QLabel( this );
    this->ghostTextLabel->setObjectName( QString::fromUtf8("ghostTextLabel") );
    this->ghostTextLabel->setScaledContents(false);
    this->ghostTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignHCenter|Qt::AlignVCenter);
    this->ghostTextLabel->setText( QString::fromUtf8("Ghost") );

    this->leftTextLabel = new QLabel( this );
    this->leftTextLabel->setObjectName( QString::fromUtf8("ghostTextLabel") );
    this->leftTextLabel->setScaledContents(false);
    this->leftTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->leftTextLabel->setText( QString::fromUtf8("Left Hand:") );

    this->levelLeftAccent = new QtSvgDialWithButtons( this );
    this->levelLeftAccent->setDialSkin( QString::fromUtf8("levelDial") );
    this->levelLeftAccent->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->levelLeftAccent->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->levelLeftAccent->setMinimum(1);
    this->levelLeftAccent->setMaximum(100);
    this->levelLeftAccent->dial->setNubSizeToRadiusRatio(0.6);
    this->levelLeftAccent->dial->setNubRadius(0.5);
    this->levelLeftAccent->setValue(80);
    connect(this->levelLeftAccent, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));

    this->levelLeftNormal = new QtSvgDialWithButtons( this );
    this->levelLeftNormal->setDialSkin( QString::fromUtf8("levelDial") );
    this->levelLeftNormal->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->levelLeftNormal->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->levelLeftNormal->setMinimum(1);
    this->levelLeftNormal->setMaximum(100);
    this->levelLeftNormal->dial->setNubSizeToRadiusRatio(0.6);
    this->levelLeftNormal->dial->setNubRadius(0.5);
    this->levelLeftNormal->setValue(50);
    connect(this->levelLeftNormal, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));

    this->levelLeftGhost = new QtSvgDialWithButtons( this );
    this->levelLeftGhost->setDialSkin( QString::fromUtf8("levelDial") );
    this->levelLeftGhost->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->levelLeftGhost->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->levelLeftGhost->setMinimum(1);
    this->levelLeftGhost->setMaximum(100);
    this->levelLeftGhost->dial->setNubSizeToRadiusRatio(0.6);
    this->levelLeftGhost->dial->setNubRadius(0.5);
    this->levelLeftGhost->setValue(30);
    connect(this->levelLeftGhost, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));

    this->rightTextLabel = new QLabel( this );
    this->rightTextLabel->setObjectName( QString::fromUtf8("ghostTextLabel") );
    this->rightTextLabel->setScaledContents(false);
    this->rightTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->rightTextLabel->setText( QString::fromUtf8("Right Hand:") );

    this->levelRightAccent = new QtSvgDialWithButtons( this );
    this->levelRightAccent->setDialSkin( QString::fromUtf8("levelDial") );
    this->levelRightAccent->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->levelRightAccent->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->levelRightAccent->setMinimum(1);
    this->levelRightAccent->setMaximum(100);
    this->levelRightAccent->dial->setNubSizeToRadiusRatio(0.6);
    this->levelRightAccent->dial->setNubRadius(0.5);
    this->levelRightAccent->setValue(80);
    connect(this->levelRightAccent, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));

    this->levelRightNormal = new QtSvgDialWithButtons( this );
    this->levelRightNormal->setDialSkin( QString::fromUtf8("levelDial") );
    this->levelRightNormal->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->levelRightNormal->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->levelRightNormal->setMinimum(1);
    this->levelRightNormal->setMaximum(100);
    this->levelRightNormal->dial->setNubSizeToRadiusRatio(0.6);
    this->levelRightNormal->dial->setNubRadius(0.5);
    this->levelRightNormal->setValue(50);
    connect(this->levelRightNormal, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));

    this->levelRightGhost = new QtSvgDialWithButtons( this );
    this->levelRightGhost->setDialSkin( QString::fromUtf8("levelDial") );
    this->levelRightGhost->setButtonUpSkin( QString::fromUtf8("upButton") );
    this->levelRightGhost->setButtonDownSkin( QString::fromUtf8("downButton") );
    this->levelRightGhost->setMinimum(1);
    this->levelRightGhost->setMaximum(100);
    this->levelRightGhost->dial->setNubSizeToRadiusRatio(0.6);
    this->levelRightGhost->dial->setNubRadius(0.5);
    this->levelRightGhost->setValue(30);
    connect(this->levelRightGhost, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));

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
    this->clickGenerator = new libTheClick::ClickGenerator_Rudiments();
    this->pasLeftAccentDrumKitID      = 0;
    this->pasLeftAccentInstrumentID   = 1;
    this->pasLeftNormalDrumKitID      = 0;
    this->pasLeftNormalInstrumentID   = 1;
    this->pasLeftGhostDrumKitID       = 0;
    this->pasLeftGhostInstrumentID    = 1;
    this->pasRightAccentDrumKitID     = 0;
    this->pasRightAccentInstrumentID  = 5;
    this->pasRightNormalDrumKitID     = 0;
    this->pasRightNormalInstrumentID  = 5;
    this->pasRightGhostDrumKitID      = 0;
    this->pasRightGhostInstrumentID   = 5;

    this->clickGenerator->setRudimentsID( this->rudimentsComboBox->currentIndex() + 1 );
    this->levelChanged(0); //load SoundElements into clickgenerator

    //update valume
    this->clickgenID = CLICKGEN_DISABLED_VALUE;
    this->volumeChanged( this->volumeSlider->value() );
    this->muteToggleSwitch->setChecked(true);
    this->muteSwitch();
}

ClickGeneratorPASWidget::~ClickGeneratorPASWidget()
{

}

//*****************************
//********** METHODS **********
//*****************************
int ClickGeneratorPASWidget::heightForWidth(int w) const
{
    int dialWithButtonsHeight = ScaleInformation::getInstance()->getHeightDialWithButtons();
//    int dialWithButtonsWidth = ScaleInformation::getInstance()->getWidthDialWithButtons();
    int muteHeight = ScaleInformation::getInstance()->getHeightMuteToggleSwitch();

    int curHeight = DISTANCE_Y_TOP;
    curHeight += dialWithButtonsHeight + SPACE_Y;
    curHeight += dialWithButtonsHeight + SPACE_Y;
    curHeight += dialWithButtonsHeight + SPACE_Y;
    curHeight += dialWithButtonsHeight + SPACE_Y;
    curHeight += muteHeight + SPACE_Y;

    curHeight += -SPACE_Y + DISTANCE_Y_BOTTOM;

    return curHeight;
}

QSize ClickGeneratorPASWidget::sizeHint() const
{
    return QSize(this->parentWidget()->parentWidget()->geometry().width(), this->heightForWidth(this->parentWidget()->parentWidget()->geometry().width()));
}

int ClickGeneratorPASWidget::getMinimumWidthForMainWindowHeight(int h) const
{
    return 4 * (ScaleInformation::getInstance()->getWidthDialWithButtonsForMainWindowHeight(h) + SPACE_X) + DISTANCE_X_LEFT + DISTANCE_X_RIGHT;
}

QList<XToXAssociationAbstractWidget*>* ClickGeneratorPASWidget::XToXAssociationWidgetFactory()
{
    QList<XToXAssociationAbstractWidget*>* ret = new QList<XToXAssociationAbstractWidget*>;
    ClickGeneratorSoundWidget* nextWidget;

    nextWidget = new ClickGeneratorSoundWidget(this, PAS_SOUNDID_LEFT_ACCENT);
    nextWidget->setText( QString::fromUtf8("Left Accent") );
    ret->push_back( nextWidget );

    nextWidget = new ClickGeneratorSoundWidget(this, PAS_SOUNDID_LEFT_NORMAL);
    nextWidget->setText( QString::fromUtf8("Left Normal") );
    ret->push_back( nextWidget );

    nextWidget = new ClickGeneratorSoundWidget(this, PAS_SOUNDID_LEFT_GHOST);
    nextWidget->setText( QString::fromUtf8("Left Ghost") );
    ret->push_back( nextWidget );

    nextWidget = new ClickGeneratorSoundWidget(this, PAS_SOUNDID_RIGHT_ACCENT);
    nextWidget->setText( QString::fromUtf8("Right Accent") );
    ret->push_back( nextWidget );

    nextWidget = new ClickGeneratorSoundWidget(this, PAS_SOUNDID_RIGHT_NORMAL);
    nextWidget->setText( QString::fromUtf8("Right Normal") );
    ret->push_back( nextWidget );

    nextWidget = new ClickGeneratorSoundWidget(this, PAS_SOUNDID_RIGHT_GHOST);
    nextWidget->setText( QString::fromUtf8("Right Ghost") );
    ret->push_back( nextWidget );

    //return list
    return ret;
}

void ClickGeneratorPASWidget::setSoundConfiguration(clickgensound_id cgsID, drumkit_id dkID, instrument_id instrumentID)
{
    //update configuration
    switch(cgsID)
    {
        case PAS_SOUNDID_LEFT_ACCENT:
            this->pasLeftAccentDrumKitID = dkID;
            this->pasLeftAccentInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_LEFT_NORMAL:
            this->pasLeftNormalDrumKitID = dkID;
            this->pasLeftNormalInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_LEFT_GHOST:
            this->pasLeftGhostDrumKitID = dkID;
            this->pasLeftGhostInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_RIGHT_ACCENT:
            this->pasRightAccentDrumKitID = dkID;
            this->pasRightAccentInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_RIGHT_NORMAL:
            this->pasRightNormalDrumKitID = dkID;
            this->pasRightNormalInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_RIGHT_GHOST:
            this->pasRightGhostDrumKitID = dkID;
            this->pasRightGhostInstrumentID = instrumentID;
            break;
    }

    //take over configuration
    this->levelChanged(0); //value is ignored
}

ClickGeneratorAbstractWidget::clickgensound_strings ClickGeneratorPASWidget::getClickGenSoundStrings(clickgensound_id cgsID)
{
    clickgensound_strings ret;
    drumkit_id drumkitID = 0;
    instrument_id instrumentID = 0;

    switch(cgsID)
    {
        case PAS_SOUNDID_LEFT_ACCENT:
            drumkitID = this->pasLeftAccentDrumKitID;
            instrumentID = this->pasLeftAccentInstrumentID;
            break;
        case PAS_SOUNDID_LEFT_NORMAL:
            drumkitID = this->pasLeftNormalDrumKitID;
            instrumentID = this->pasLeftNormalInstrumentID;
            break;
        case PAS_SOUNDID_LEFT_GHOST:
            drumkitID = this->pasLeftGhostDrumKitID;
            instrumentID = this->pasLeftGhostInstrumentID;
            break;
        case PAS_SOUNDID_RIGHT_ACCENT:
            drumkitID = this->pasRightAccentDrumKitID;
            instrumentID = this->pasRightAccentInstrumentID;
            break;
        case PAS_SOUNDID_RIGHT_NORMAL:
            drumkitID = this->pasRightNormalDrumKitID;
            instrumentID = this->pasRightNormalInstrumentID;
            break;
        case PAS_SOUNDID_RIGHT_GHOST:
            drumkitID = this->pasRightGhostDrumKitID;
            instrumentID = this->pasRightGhostInstrumentID;
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

void ClickGeneratorPASWidget::setClickGenSoundStrings(clickgensound_id cgsID, clickgensound_strings cgsSt)
{
    drumkit_id    drumkitID    = this->clickController->getSoundBase()->getDrumKitID( cgsSt.drumkitName.toStdString() ) ;
    instrument_id instrumentID = this->clickController->getSoundBase()->getInstrumentID( cgsSt.drumkitName.toStdString(), cgsSt.instrumentName.toStdString() ) ;

    //update configuration
    switch(cgsID)
    {
        case PAS_SOUNDID_LEFT_ACCENT:
            this->pasLeftAccentDrumKitID = drumkitID;
            this->pasLeftAccentInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_LEFT_NORMAL:
            this->pasLeftNormalDrumKitID = drumkitID;
            this->pasLeftNormalInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_LEFT_GHOST:
            this->pasLeftGhostDrumKitID = drumkitID;
            this->pasLeftGhostInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_RIGHT_ACCENT:
            this->pasRightAccentDrumKitID = drumkitID;
            this->pasRightAccentInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_RIGHT_NORMAL:
            this->pasRightNormalDrumKitID = drumkitID;
            this->pasRightNormalInstrumentID = instrumentID;
            break;
        case PAS_SOUNDID_RIGHT_GHOST:
            this->pasRightGhostDrumKitID = drumkitID;
            this->pasRightGhostInstrumentID = instrumentID;
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
void ClickGeneratorPASWidget::resizeEvent ( QResizeEvent * event )
{
    int curHeight = DISTANCE_Y_TOP;
    int dialWithButtonsHeight = ScaleInformation::getInstance()->getHeightDialWithButtons();
    int dialWithButtonsWidth = ScaleInformation::getInstance()->getWidthDialWithButtons();
    int muteHeight = ScaleInformation::getInstance()->getHeightMuteToggleSwitch();
    int muteWidth = ScaleInformation::getInstance()->getWidthMuteToggleSwitch();
    int textPixelSize = ScaleInformation::getInstance()->getPixelSizeNormalText();
    QFont fontNextElement;

    this->rudimentTextLabel->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, this->size().width(), dialWithButtonsHeight) );
    fontNextElement = this->rudimentTextLabel->font();
    fontNextElement.setPixelSize( textPixelSize );
    this->rudimentTextLabel->setFont( fontNextElement );
    this->rudimentsComboBox->setFont( fontNextElement );
    this->rudimentsComboBox->setGeometry( QRect(DISTANCE_X_LEFT + dialWithButtonsWidth + SPACE_X, curHeight, this->width() - dialWithButtonsWidth - SPACE_X - DISTANCE_X_LEFT - DISTANCE_X_RIGHT, dialWithButtonsHeight) );
    this->rudimentsComboBox->update();
    curHeight += dialWithButtonsHeight + SPACE_Y;

    this->accentTextLabel->setGeometry( QRect(DISTANCE_X_LEFT + dialWithButtonsWidth + SPACE_X, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->accentTextLabel->setFont( fontNextElement );
    this->normalTextLabel->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X)*2, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->normalTextLabel->setFont( fontNextElement );
    this->ghostTextLabel->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X)*3, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->ghostTextLabel->setFont( fontNextElement );
    curHeight += dialWithButtonsHeight + SPACE_Y;

    this->leftTextLabel->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->leftTextLabel->setFont( fontNextElement );
    this->levelLeftAccent->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X)*1, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->levelLeftNormal->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X)*2, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->levelLeftGhost->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X)*3, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    curHeight += dialWithButtonsHeight + SPACE_Y;

    this->rightTextLabel->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->rightTextLabel->setFont( fontNextElement );
    this->levelRightAccent->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X)*1, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->levelRightNormal->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X)*2, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    this->levelRightGhost->setGeometry( QRect(DISTANCE_X_LEFT + (dialWithButtonsWidth + SPACE_X)*3, curHeight, dialWithButtonsWidth, dialWithButtonsHeight) );
    curHeight += dialWithButtonsHeight + SPACE_Y;

    this->muteToggleSwitch->setGeometry( QRect(DISTANCE_X_LEFT, curHeight, muteWidth, muteHeight) );
    this->volumeSlider->setGeometry( QRect(DISTANCE_X_LEFT + SPACE_X + muteWidth, curHeight + (muteHeight - dialWithButtonsHeight) / 2, this->size().width() - DISTANCE_X_LEFT - DISTANCE_X_RIGHT - SPACE_X - muteWidth, dialWithButtonsHeight) );

    update();
}

void ClickGeneratorPASWidget::rudimentChanged(int value)
{
    this->clickGenerator->setRudimentsID( value + 1 );
}

void ClickGeneratorPASWidget::levelChanged(int)
{
    this->clickGenerator->setSoundElement(LEFT, ACCENT, this->clickController->getSoundBase()->getSoundElement(
        this->pasLeftAccentDrumKitID,
        this->pasLeftAccentInstrumentID,
        (double)this->levelLeftAccent->value() / (double)this->levelLeftAccent->maximum())
    );

    this->clickGenerator->setSoundElement(LEFT, NORMAL, this->clickController->getSoundBase()->getSoundElement(
        this->pasLeftAccentDrumKitID,
        this->pasLeftAccentInstrumentID,
        (double)this->levelLeftNormal->value() / (double)this->levelLeftNormal->maximum())
    );

    this->clickGenerator->setSoundElement(LEFT, GHOST, this->clickController->getSoundBase()->getSoundElement(
        this->pasLeftAccentDrumKitID,
        this->pasLeftAccentInstrumentID,
        (double)this->levelLeftGhost->value() / (double)this->levelLeftGhost->maximum())
    );

    this->clickGenerator->setSoundElement(RIGHT, ACCENT, this->clickController->getSoundBase()->getSoundElement(
        this->pasRightAccentDrumKitID,
        this->pasRightAccentInstrumentID,
        (double)this->levelRightAccent->value() / (double)this->levelRightAccent->maximum())
    );

    this->clickGenerator->setSoundElement(RIGHT, NORMAL, this->clickController->getSoundBase()->getSoundElement(
        this->pasRightAccentDrumKitID,
        this->pasRightAccentInstrumentID,
        (double)this->levelRightNormal->value() / (double)this->levelRightNormal->maximum())
    );

    this->clickGenerator->setSoundElement(RIGHT, GHOST, this->clickController->getSoundBase()->getSoundElement(
        this->pasRightAccentDrumKitID,
        this->pasRightAccentInstrumentID,
        (double)this->levelRightGhost->value() / (double)this->levelRightGhost->maximum())
    );
}

void ClickGeneratorPASWidget::volumeChanged(int)
{
    if(this->clickgenID != CLICKGEN_DISABLED_VALUE)
        this->clickController->setVolumeforClickGenerator(this->clickgenID, (float)this->volumeSlider->value() / (float)this->volumeSlider->maximum());
}

void ClickGeneratorPASWidget::muteSwitch()
{
    if(!this->muteToggleSwitch->isChecked())
    {
        this->clickgenID = this->clickController->addClickGenerator( this->clickGenerator, (float)this->volumeSlider->value() / (float)this->volumeSlider->maximum() );
    }
    else
    {
        if(this->clickgenID != CLICKGEN_DISABLED_VALUE)
            this->clickController->removeClickGenerator( this->clickgenID );

        this->clickgenID = CLICKGEN_DISABLED_VALUE;
    }
}
