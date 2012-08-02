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

#include "widgets/ScrollListOfWidgets/WidgetPlate.h"

//debug
#include <iostream>

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
WidgetPlate::WidgetPlate(QWidget *parent)
    : QWidget(parent)
{
    //create and initialize widgets
//    this->setGeometry( QRect(0, 0, 1000,1000) );
}

WidgetPlate::~WidgetPlate()
{
    for(QList<QWidget*>::iterator it = this->widgetList.begin(); it != this->widgetList.end(); /*nothing*/)
	{
        delete *it;
        it = this->widgetList.erase(it);

		//end condition
        if(it == this->widgetList.end()) break;
	}
}

//*****************************
//********** METHODS **********
//*****************************
int WidgetPlate::heightForWidth (int w) const
{
	int h = 0;

    for(QList<QWidget*>::const_iterator it = this->widgetList.begin(); it != this->widgetList.end(); it++)
        h += (*it)->heightForWidth(w);

    return h;
}

QSize WidgetPlate::sizeHint() const
{
    QSize ret(this->parentWidget()->geometry().width(), this->heightForWidth( this->parentWidget()->geometry().width() ));

    return ret;
}

//void WidgetPlate::update()
//{
//    //place widgets
//    this->resizeEvent(NULL);

//    //call update of this class
//    QWidget::update();

//    //update also parent because sizeHint() of this object changed
//    if(this->parent() != NULL)
//        this->parentWidget()->update();
//}

void WidgetPlate::addWidget(QWidget* w)
{
    //check if widget is already in list
    if(this->widgetList.contains(w))
        throw WidgetPlateException_WidgetAlreadAvailable();

    //set this as parent and store widget
    w->setParent(this);
    this->widgetList.push_back(w);
    QWidget::setMinimumSize( this->sizeHint() );
    this->update();
}

void WidgetPlate::setGeometry ( const QRect & g )
{
    QWidget::setGeometry(g);
    this->update();
}

void WidgetPlate::resize( const QSize& s)
{
    this->setMinimumSize(s);
    QWidget::resize(s);
}

//*****************************
//********** SIGNALS **********
//*****************************


//*****************************
//*********** SLOTS ***********
//*****************************
void WidgetPlate::resizeEvent ( QResizeEvent * event )
{
    //place all widget on correct place
    int h = 0;
    for(QList<QWidget*>::iterator it = this->widgetList.begin(); it != this->widgetList.end(); it++)
    {
        int height = (*it)->heightForWidth( this->parentWidget()->width() );
        (*it)->setGeometry( QRect(0, h, this->parentWidget()->width(), height) );
        h += (*it)->sizeHint().height();
    }

    //set minimin size of widget
    QWidget::setMinimumSize( this->sizeHint() );
}
