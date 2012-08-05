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

    this->signalMapper_left = new QSignalMapper(this);
    this->signalMapper_right = new QSignalMapper(this);
    connect(this->signalMapper_left, SIGNAL(mapped(QObject*)), this, SLOT(clicked_left(QObject*)));
    connect(this->signalMapper_right, SIGNAL(mapped(QObject*)), this, SLOT(clicked_right(QObject*)));
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
    connect(w, SIGNAL(clicked()), this->signalMapper_left, SLOT(map()));
    this->signalMapper_left->setMapping(w, (QObject*)w);
}

void XToXAssociationWidget::pushBackRightWidget(QAbstractButton* w)
{
    this->rightScrollList->addWidget(w);
    connect(w, SIGNAL(clicked()), this->signalMapper_right, SLOT(map()));
    this->signalMapper_right->setMapping(w, (QObject*)w);
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

void XToXAssociationWidget::updateSelectionOnRightSide() const
{
    //select elements on the right side according to associationList
    Association a;
    a.left  = this->getSelectionOnLeftSide();

    foreach(QObject* e, *this->rightScrollList->widgetPlate->getConstWidgetList())
    {
        a.right = (QAbstractButton*)e;

        if( this->associationList.contains(a) )
            ((QAbstractButton*)e)->setChecked(true);
        else
            ((QAbstractButton*)e)->setChecked(false);
    }
}

QAbstractButton* XToXAssociationWidget::getSelectionOnLeftSide() const
{
    QAbstractButton* ret = NULL;

    foreach(QObject* e, *this->leftScrollList->widgetPlate->getConstWidgetList())
    {
        if( ((QAbstractButton*)e)->isChecked() )
        {
            ret = (QAbstractButton*)e;
            break;
        }
    }

    return ret;
}

//*****************************
//********** SIGNALS **********
//*****************************


//*****************************
//*********** SLOTS ***********
//*****************************
void XToXAssociationWidget::clicked_left(QObject* o)
{
    //debug
//    std::cout << "clicked_left" << std::endl;

    //only select one element on the left side
    foreach(QObject* e, *this->leftScrollList->widgetPlate->getConstWidgetList())
    {
        if((QObject*)e != o)
            ((QAbstractButton*)e)->setChecked(false);
    }

    //select elements on the right side according to associationList
    this->updateSelectionOnRightSide();
}

void XToXAssociationWidget::clicked_right(QObject* o)
{
    //debug
//    std::cout << "clicked_right" << std::endl;

    //only do job if there is a selection on the left side
    if(this->getSelectionOnLeftSide() != NULL)
    {

        //update associationList
        if(this->type == N_TO_ONE)
        {
            //remove all associations which contain the left element
            for(QList<Association>::iterator it = this->associationList.begin(); it != this->associationList.end(); /*nothing*/)
            {
                if((*it).left == this->getSelectionOnLeftSide())
                    it = this->associationList.erase(it);
                else
                    it++;

                //end condition
                if(it == this->associationList.end()) break;
            }

            //add new association
            Association a;
            a.left = this->getSelectionOnLeftSide();
            a.right = (QAbstractButton*)o;
            this->associationList.push_back(a);
        }
    //    else if(this->type == ONE_TO_N)
    //    {

    //    }
    //    else if(this->type == ONE_TO_ONE)
    //    {

    //    }
    }

    //select elements on the right side according to associationList
    this->updateSelectionOnRightSide();
}
