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

#ifndef SCROLLLISTOFWIDGETS_H
#define SCROLLLISTOFWIDGETS_H

#include <QWidget>
#include <QScrollArea>
#include "widgets/ScrollListOfWidgets/WidgetPlate.h"

class ScrollListOfWidgets : public QWidget
{
    Q_OBJECT
    
    //********** (DE/CON)STRUCTORS **********
    public:
        ScrollListOfWidgets(QWidget *parent = 0);
        ~ScrollListOfWidgets();

    private:

    //********** ATTRIBUTES **********
    public: 
        //GUI elements
        QScrollArea*    scrollArea;
        WidgetPlate*    widgetPlate;

    protected: 
        
    private:
        
    //********** METHODS **********
    public: 
        void setGeometry ( const QRect & g );
        void addWidget(QWidget* w) {this->widgetPlate->addWidget(w);}

    protected: 
        
    private:

    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:



};

#endif // SCROLLLISTOFWIDGETS_H
