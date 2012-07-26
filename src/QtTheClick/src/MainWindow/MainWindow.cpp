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

#include "MainWindow/MainWindow.h"
#include "widgets/svgtoggleswitch/qtsvgtoggleswitch.h"
#include "MainWindow/ScaleInformation.h"

#include "boost/bind.hpp"
#include <limits>

//debug
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //initialize attributes
    this->clickController = new libTheClick::ClickController();

    //create form
    this->theClickForm = new Ui::TheClickForm();
    this->theClickForm->setupUi( this );

    //create Widgets
    this->speedWidget = new SpeedWidget( this->theClickForm->speedGroupBox );
    this->speedWidget->speedDial->setMinimum(20);
    this->speedWidget->speedDial->setMaximum(300);
    this->speedWidget->setObjectName( QString::fromUtf8("speedWidget") );
    this->speedWidget->setGeometry( QRect(10,10,170,620) );
//    this->speedWidget->setGeometry( QRect(10,10,this->theClickForm->speedGroupBox->width()-20,this->theClickForm->speedGroupBox->height()-20) );
    this->speedWidget->show();

    this->clickGeneratorScrollListOfWidgets = new ScrollListOfWidgets( this->theClickForm->clickGeneratorGroupBox );
    this->clickGeneratorScrollListOfWidgets->setGeometry( QRect(0,20,this->theClickForm->clickGeneratorGroupBox->width(),this->theClickForm->clickGeneratorGroupBox->height()) );

    this->clickGeneratorDivisionWidget = new ClickGeneratorDivisionWidget(this->clickController);
    this->clickGeneratorScrollListOfWidgets->addWidget( this->clickGeneratorDivisionWidget);
    connect(this->clickGeneratorDivisionWidget, SIGNAL(shouldResize()), this, SLOT(shouldResize()) );

    this->clickGeneratorXoYWidget = new ClickGeneratorXoYWidget(this->clickController);
    this->clickGeneratorScrollListOfWidgets->addWidget( this->clickGeneratorXoYWidget );
    connect(this->clickGeneratorXoYWidget, SIGNAL(shouldResize()), this, SLOT(shouldResize()) );

    this->clickGeneratorPASWidget = new ClickGeneratorPASWidget(this->clickController);
    this->clickGeneratorScrollListOfWidgets->addWidget( this->clickGeneratorPASWidget );
    connect(this->clickGeneratorPASWidget, SIGNAL(shouldResize()), this, SLOT(shouldResize()) );

    //connect signals to private slots
    connect(this->speedWidget->p10Button, SIGNAL(clicked()), this, SLOT(speedPlus10())  );
    connect(this->speedWidget->p5Button, SIGNAL(clicked()), this, SLOT(speedPlus05())  );
    connect(this->speedWidget->p2Button, SIGNAL(clicked()), this, SLOT(speedPlus02())  );
    connect(this->speedWidget->p1Button, SIGNAL(clicked()), this, SLOT(speedPlus01())  );
    connect(this->speedWidget->m10Button, SIGNAL(clicked()), this, SLOT(speedMinus10()) );
    connect(this->speedWidget->m5Button, SIGNAL(clicked()), this, SLOT(speedMinus05()) );
    connect(this->speedWidget->m2Button, SIGNAL(clicked()), this, SLOT(speedMinus02()) );
    connect(this->speedWidget->m1Button, SIGNAL(clicked()), this, SLOT(speedMinus01()) );
    connect(this->speedWidget->speedDial, SIGNAL(valueChanged(int)), this, SLOT(speedDialValueChanged(int)));

    connect(this->speedWidget->playToggleSwitch, SIGNAL(clicked()), this, SLOT(startButton()) );
    connect(this->speedWidget->stopButton,  SIGNAL(clicked()), this, SLOT(stopButton()) );
    connect(this->speedWidget->tapButton,  SIGNAL(clicked()), this, SLOT(tapButton()) );

    //initialize libTheClick
    this->cgDummyBeatCount = new libTheClick::ClickGenerator_DummyBeatCount();

    //set initialization values
    this->speedWidget->speedDial->setValue(100); //also sends signal

    //set speed in ClickController
    this->speedDialValueChanged( this->speedWidget->speedDial->value() );

    //set call back function
    this->cgDummyBeatCount->setBeatCountCallbackFunction( boost::bind( &MainWindow::theClickBeatsCallBack, &(*this) , _1) );
    this->clickController->addClickGenerator(this->cgDummyBeatCount, 0.0f);

    //bring MainWindow to appropriate size
    QResizeEvent re(this->size(), this->size());
    this->resizeEvent(&re);
}

MainWindow::~MainWindow()
{
    //stop playback
    this->clickController->stop();

    //delete widgets
    if(this->speedWidget != NULL)
        delete this->speedWidget;

    //delete attributes
    if(this->theClickForm != NULL)
        delete this->theClickForm;

    if(this->clickController != NULL)
        delete this->clickController;

//    if(this->speedWidget != NULL)
//        delete this->speedWidget;

//    if(this->clickGeneratorDivisionWidget != NULL)
//        delete this->clickGeneratorDivisionWidget;

//    if(this->clickGeneratorScrollListOfWidgets != NULL)
//        delete this->clickGeneratorScrollListOfWidgets;
}

void MainWindow::speedPlus10()
{
    this->speedWidget->speedDial->setValue( this->speedWidget->speedDial->value() + 10 );
}

void MainWindow::speedPlus05()
{
    this->speedWidget->speedDial->setValue( this->speedWidget->speedDial->value() + 5 );
}

void MainWindow::speedPlus02()
{
    this->speedWidget->speedDial->setValue( this->speedWidget->speedDial->value() + 2 );
}

void MainWindow::speedPlus01()
{
    this->speedWidget->speedDial->setValue( this->speedWidget->speedDial->value() + 1 );
}

void MainWindow::speedMinus10()
{
    this->speedWidget->speedDial->setValue( this->speedWidget->speedDial->value() - 10 );
}

void MainWindow::speedMinus05()
{
    this->speedWidget->speedDial->setValue( this->speedWidget->speedDial->value() - 5 );
}

void MainWindow::speedMinus02()
{
    this->speedWidget->speedDial->setValue( this->speedWidget->speedDial->value() - 2 );
}

void MainWindow::speedMinus01()
{
    this->speedWidget->speedDial->setValue( this->speedWidget->speedDial->value() - 1 );
}

void MainWindow::speedDialValueChanged(int value)
{
    this->speedWidget->bpmSpeedLabel->setText( QString::number(value) );
    this->clickController->setBeatsPerMinute( value );
}

void MainWindow::startButton()
{
    //control libTheClick
    if( this->speedWidget->playToggleSwitch->isChecked() )
        this->clickController->start();
    else
        this->clickController->stop();
}

void MainWindow::stopButton()
{
    //control libTheClick
    this->speedWidget->playToggleSwitch->setChecked(false);
    this->speedWidget->beatCountLabel->setText( QString::number(0) );
    this->startButton();
    this->clickController->reset();
}

void MainWindow::tapButton()
{
    //add new element to list
    this->tapList.push_back( QDateTime::currentDateTime() );

    //delete elements which are to old
    for(std::list<QDateTime>::iterator it = this->tapList.begin(); it != this->tapList.end(); /*nothing*/)
    {
        if(it->msecsTo(QDateTime::currentDateTime()) > 5000 )
            it = this->tapList.erase(it);
        else
            it++;

        //end condition
        if(it == this->tapList.end())
            break;
    }

    //determine new speed
    if(this->tapList.size() > 5)
    {
        //erase first element
        this->tapList.erase( this->tapList.begin() );

        //determine new speed
        this->speedWidget->speedDial->setValue( 4 * 60 * 1000 / this->tapList.front().msecsTo( this->tapList.back() ) );
    }
}

void MainWindow::theClickBeatsCallBack(int beats)
{
    //only update gui in play mode
    if(this->speedWidget->playToggleSwitch->isChecked())
    {
        //update beatCountLabel
        this->speedWidget->beatCountLabel->setText( QString::number(beats) );
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    //call methode of parent class
    QMainWindow::resizeEvent(event);

    //calcluate position and size for given event.size()
    int newHeight = event->size().height();
    int newWidth = event->size().width();

    double ratioSpeedWidget = this->speedWidget->heightForWidth(1); //just to get ratio
    int newWidthSpeedWidget = (newHeight-20) / ratioSpeedWidget;

    int newWidthClickGeneratorWidgets = newWidth - newWidthSpeedWidget - 70;

    //update ScaleInformation signleton
    ScaleInformation::getInstance()->setMainWindowSize( event->size() );


    //determine minimum width of ClickGenerator Widgets
    int minimumWidthClickGeneratorWidgets = 0;
    if(this->clickGeneratorDivisionWidget->getMinimimWidthForMainWindowHeight( newHeight ) > minimumWidthClickGeneratorWidgets )
        minimumWidthClickGeneratorWidgets = this->clickGeneratorDivisionWidget->getMinimimWidthForMainWindowHeight( event->size().height() );

    if(this->clickGeneratorXoYWidget->getMinimimWidthForMainWindowHeight( newHeight ) > minimumWidthClickGeneratorWidgets )
        minimumWidthClickGeneratorWidgets = this->clickGeneratorXoYWidget->getMinimimWidthForMainWindowHeight( event->size().height() );

    if(this->clickGeneratorPASWidget->getMinimimWidthForMainWindowHeight( newHeight ) > minimumWidthClickGeneratorWidgets )
        minimumWidthClickGeneratorWidgets = this->clickGeneratorPASWidget->getMinimimWidthForMainWindowHeight( event->size().height() );

    //determine minimumWidthForMainWindow
    if(minimumWidthClickGeneratorWidgets > newWidthClickGeneratorWidgets)
    {
        newWidth += minimumWidthClickGeneratorWidgets - newWidthClickGeneratorWidgets;
        newWidthClickGeneratorWidgets = minimumWidthClickGeneratorWidgets;
        this->resize(newWidth, newHeight);
    }


    //resize speedWidget
    this->speedWidget->setGeometry(10, 20, newWidthSpeedWidget, newHeight-20);
    this->theClickForm->speedGroupBox->setGeometry(newWidth-newWidthSpeedWidget-30, 0, newWidthSpeedWidget+20, newHeight-10);

    //debug
//    QPalette pal =  this->speedWidget->palette();
//    pal.setColor(QPalette::Background, Qt::blue);
//    this->speedWidget->setPalette(pal);
//    this->speedWidget->setBackgroundRole( QPalette::Background );
//    this->speedWidget->setAutoFillBackground(true);
//    this->speedWidget->repaint();

    //resize ClickGenerators
    this->clickGeneratorScrollListOfWidgets->setGeometry( QRect(10, 20, newWidthClickGeneratorWidgets, newHeight-20) );
    this->theClickForm->clickGeneratorGroupBox->setGeometry(10, 0, newWidthClickGeneratorWidgets+20, newHeight-10);
}

void MainWindow::shouldResize()
{
    QResizeEvent re(this->size(), this->size());
    this->resizeEvent(&re);
}
