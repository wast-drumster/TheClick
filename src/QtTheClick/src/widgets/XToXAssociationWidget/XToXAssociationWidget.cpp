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

#include "widgets/XToXAssociationWidget/XToXAssociationWidget.h"

//debug
#include <iostream>

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
XToXAssociationWidget::XToXAssociationWidget(AssiciationType type, QWidget *parent)
  : QWidget(parent),
    type(type)
{
    //create and initialize widgets
    this->leftScrollList = new ScrollListOfWidgets( this );
    this->rightScrollList = new ScrollListOfWidgets( this );
}

XToXAssociationWidget::~XToXAssociationWidget()
{
}

//*****************************
//********** METHODS **********
//*****************************
void XToXAssociationWidget::setGeometry ( const QRect & g )
{
    QWidget::setGeometry(g);

    this->leftScrollList->setGeometry( QRect(0, 0, g.width()*1/3, g.height()) );
    this->rightScrollList->setGeometry( QRect(g.width()*2/3, 0, g.width()*1/3, g.height()) );
}

void XToXAssociationWidget::pushBackLeftWidget(QAbstractButton* w)
{
    this->leftScrollList->addWidget(w);
    connect(w, SIGNAL(clicked()), this, SLOT(clicked_left()));
}

void XToXAssociationWidget::pushBackRightWidget(QAbstractButton* w)
{
    this->rightScrollList->addWidget(w);
    connect(w, SIGNAL(clicked()), this, SLOT(clicked_right()));
}

void XToXAssociationWidget::add_Association(QAbstractButton* left, QAbstractButton* right)
{
    //check if parameters are already in lists
    if(!this->leftScrollList->containsWidget(left) || !this->rightScrollList->containsWidget(right))
        throw XToXAssociationWidgetException_WidgetNotAvailable();

    //add association
    Association as;
    as.left  = left;
    as.right = right;
    this->associationList.push_back(as);
}

//*****************************
//********** SIGNALS **********
//*****************************


//*****************************
//*********** SLOTS ***********
//*****************************
void XToXAssociationWidget::clicked_left()
{
    std::cout << "clicked_left" << std::endl;
}

void XToXAssociationWidget::clicked_right()
{
    std::cout << "clicked_right" << std::endl;
}
