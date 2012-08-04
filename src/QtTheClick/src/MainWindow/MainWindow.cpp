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

#include "MainWindow/MainWindow.h"
#include "widgets/svgtoggleswitch/qtsvgtoggleswitch.h"
#include "MainWindow/ScaleInformation.h"
#include "MainWindow/SoundConfigurationTab/SoundElementWidget.h"

#include "boost/bind.hpp"

#include <QCoreApplication> //for path of application
#include <QDir> //for path of home directory
#include <QString>
#include <QStringList>

#include <limits>

//debug
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //initialize attributes
    this->clickController = new libTheClick::ClickController();

    //create elements for drumkitPathStaticList
    //Q_OS_??? for operating system (e.g. DARWIN == MAC, WIN32, LINUX); Q_WS_??? for window system (e.g. X11, WIN32, MACX)
    #ifdef Q_OS_MAC
        this->drumkitPathStaticList.push_back( QCoreApplication::applicationDirPath() + "/../Resources/drumkits" );
        this->drumkitPathStaticList.push_back( QDir::homePath() + "/Library/Application Support/Hydrogen/drumkits" );
    #endif
    #ifdef Q_OS_LINUX
        this->drumkitPathStaticList.push_back( QCoreApplication::applicationDirPath() + "/drumkits" );
        this->drumkitPathStaticList.push_back( "/usr/share/hydrogen/data/drumkits" );
    #endif
    #ifdef Q_OS_WIN32
        this->drumkitPathStaticList.push_back( QCoreApplication::applicationDirPath() + "/drumkits" );
    #endif

    //load all drumkits
    for(QList<QString>::iterator it1 = this->drumkitPathStaticList.begin(); it1 != this->drumkitPathStaticList.end(); it1++)
    {
        QDir pathDir = QDir(*it1);
        QStringList dirsOfPath = pathDir.entryList(QDir::AllDirs);

        for (QStringList::const_iterator it2 = dirsOfPath.constBegin(); it2 != dirsOfPath.constEnd(); it2++)
        {
            if(*it2 != "." && *it2 != "..")
            {
                std::cout << "load: " << QDir::fromNativeSeparators(*it1 + "/" + *it2).toUtf8().constData() << std::endl;
                this->clickController->getSoundBase()->loadDrumKit( QDir::fromNativeSeparators(*it1 + "/" + *it2).toUtf8().constData() );
            }
        }
    }

    //create form
    this->theClickForm = new Ui::TheClickForm();
    this->theClickForm->setupUi( this );

    //create Widgets
    this->speedWidget = new SpeedWidget( this->clickController, this->theClickForm->speedGroupBox );
    this->speedWidget->speedDial->setMinimum(20);
    this->speedWidget->speedDial->setMaximum(300);
    this->speedWidget->setObjectName( QString::fromUtf8("speedWidget") );
    this->speedWidget->setGeometry( QRect(10,10,170,620) );
//    this->speedWidget->setGeometry( QRect(10,10,this->theClickForm->speedGroupBox->width()-20,this->theClickForm->speedGroupBox->height()-20) );
    this->speedWidget->show();

    this->clickGeneratorScrollListOfWidgets = new ScrollListOfWidgets( this->theClickForm->tabWidget );
    this->theClickForm->tabWidget->addTab(this->clickGeneratorScrollListOfWidgets, QString::fromUtf8("ClickGenerators"));
    this->clickGeneratorScrollListOfWidgets->setGeometry( QRect(0,20,this->theClickForm->tabWidget->width(),this->theClickForm->tabWidget->height()-40) );

    this->clickGeneratorDivisionWidget = new ClickGeneratorDivisionWidget(this->clickController);
    this->clickGeneratorScrollListOfWidgets->addWidget( this->clickGeneratorDivisionWidget);
    connect(this->clickGeneratorDivisionWidget, SIGNAL(shouldResize()), this, SLOT(shouldResize()) );

    this->clickGeneratorXoYWidget = new ClickGeneratorXoYWidget(this->clickController);
    this->clickGeneratorScrollListOfWidgets->addWidget( this->clickGeneratorXoYWidget );
    connect(this->clickGeneratorXoYWidget, SIGNAL(shouldResize()), this, SLOT(shouldResize()) );

    this->clickGeneratorPASWidget = new ClickGeneratorPASWidget(this->clickController);
    this->clickGeneratorScrollListOfWidgets->addWidget( this->clickGeneratorPASWidget );
    connect(this->clickGeneratorPASWidget, SIGNAL(shouldResize()), this, SLOT(shouldResize()) );

    this->m_XToXAssociationWidget = new XToXAssociationWidget( XToXAssociationWidget::ONE_TO_ONE, this->theClickForm->tabWidget );
    this->theClickForm->tabWidget->addTab(this->m_XToXAssociationWidget, QString::fromUtf8("Sound Configuration"));

    //generate widgets for XToXAssociationWidge
    {
        QList<XToXAssociationAbstractWidget*>* widgetList = this->clickGeneratorDivisionWidget->XToXAssociationWidgetFactory();

        for(QList<XToXAssociationAbstractWidget*>::iterator it = widgetList->begin(); it != widgetList->end(); it++)
            this->m_XToXAssociationWidget->pushBackLeftWidget( *it );

        delete widgetList;
    }
    {
        QList<XToXAssociationAbstractWidget*>* widgetList = this->clickGeneratorXoYWidget->XToXAssociationWidgetFactory();

        for(QList<XToXAssociationAbstractWidget*>::iterator it = widgetList->begin(); it != widgetList->end(); it++)
            this->m_XToXAssociationWidget->pushBackLeftWidget( *it );

        delete widgetList;
    }
    {
        QList<XToXAssociationAbstractWidget*>* widgetList = this->clickGeneratorPASWidget->XToXAssociationWidgetFactory();

        for(QList<XToXAssociationAbstractWidget*>::iterator it = widgetList->begin(); it != widgetList->end(); it++)
            this->m_XToXAssociationWidget->pushBackLeftWidget( *it );

        delete widgetList;
    }

    {
        std::list<SoundInformation>* sil = this->clickController->getSoundBase()->getListOfAllSoundInformations();

        for(std::list<SoundInformation>::iterator it = sil->begin(); it != sil->end(); it++)
        {
            SoundElementWidget* newSoundElementWidget = new SoundElementWidget(
                (*it).drumkitID,
                (*it).instrumentID
            );
            newSoundElementWidget->setText( QString::fromStdString( (*it).name ) );

            this->m_XToXAssociationWidget->pushBackRightWidget( newSoundElementWidget );
        }

        delete sil;
    }

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

void MainWindow::resizeEvent(QResizeEvent* event)
{
    //call methode of parent class
    QMainWindow::resizeEvent(event);

    //calcluate position and size for given event.size()
    int newHeight = event->size().height();
    int newWidth = event->size().width();

    double ratioSpeedWidget = this->speedWidget->heightForWidth(1); //just to get ratio
    int newWidthSpeedWidget = (newHeight-20) / ratioSpeedWidget;

    int newWidthTabWidgets = newWidth - newWidthSpeedWidget - 70;

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
    if(minimumWidthClickGeneratorWidgets > newWidthTabWidgets)
    {
        newWidth += minimumWidthClickGeneratorWidgets - newWidthTabWidgets;
        newWidthTabWidgets = minimumWidthClickGeneratorWidgets;
        this->resize(newWidth, newHeight);
    }


    //resize speedWidget
    this->speedWidget->setGeometry(10, 20, newWidthSpeedWidget, newHeight-20);
    this->theClickForm->speedGroupBox->setGeometry(newWidth-newWidthSpeedWidget-30, 0, newWidthSpeedWidget+20, newHeight-10);

    //debug
    QWidget* debugWidget = this->m_XToXAssociationWidget->leftScrollList;
    QPalette pal =  debugWidget->palette();
    pal.setColor(QPalette::Background, Qt::blue);
    debugWidget->setPalette(pal);
    debugWidget->setBackgroundRole( QPalette::Background );
    debugWidget->setAutoFillBackground(true);
    debugWidget->repaint();

    //resize ClickGenerators
    this->clickGeneratorScrollListOfWidgets->setGeometry( QRect(10, 20, newWidthTabWidgets, newHeight-40) );
    this->m_XToXAssociationWidget->setGeometry( QRect(10, 20, newWidthTabWidgets, newHeight-40) );
    this->theClickForm->tabWidget->setGeometry(10, 0, newWidthTabWidgets+20, newHeight-10);
}

void MainWindow::shouldResize()
{
    QResizeEvent re(this->size(), this->size());
    this->resizeEvent(&re);
}
