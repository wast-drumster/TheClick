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

#include "widgets/ScrollListOfWidgets/ScrollListOfWidgets.h"

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
ScrollListOfWidgets::ScrollListOfWidgets(QWidget *parent)
    : QWidget(parent)
{
    //create and initialize widgets
    this->scrollArea = new QScrollArea( this );
    this->scrollArea->setObjectName( QString::fromUtf8("ClickGeneratorWidget_ScrollArea") );
    this->scrollArea->setWidgetResizable( true );
    this->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    this->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->scrollArea->setGeometry( QRect(0,0,1000,1000) );
    this->scrollArea->setFrameShape( QFrame::NoFrame );

    this->widgetPlate = new WidgetPlate( this->scrollArea );
	this->widgetPlate->setObjectName( QString::fromUtf8("ClickGeneratorWidget_WidgetPlate") );
	this->scrollArea->setWidget( this->widgetPlate );
}

ScrollListOfWidgets::~ScrollListOfWidgets()
{
	if(this->scrollArea != NULL)
		delete this->scrollArea;
}

//*****************************
//********** METHODS **********
//*****************************
void ScrollListOfWidgets::setGeometry ( const QRect & g )
{
    QWidget::setGeometry(g);

    this->scrollArea->setGeometry( QRect(0, 0, g.width(), g.height()) );

    QSize widgetPlateSizeHint = this->widgetPlate->sizeHint();
    this->widgetPlate->resize( widgetPlateSizeHint );
}

//*****************************
//********** SIGNALS **********
//*****************************


//*****************************
//*********** SLOTS ***********
//*****************************

