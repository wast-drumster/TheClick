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

#ifndef ONETOONEASSICIATIONWIDGET_H
#define ONETOONEASSICIATIONWIDGET_H

#include <QWidget>

class OneToOneAssociationWidget : public QWidget
{
    Q_OBJECT
    
    //********** (DE/CON)STRUCTORS **********
    public:
        OneToOneAssociationWidget(QWidget *parent = 0);
        ~OneToOneAssociationWidget();

    private:

    //********** ATTRIBUTES **********
    public: 
        //GUI elements
        
    protected: 
        
    private:
        
    //********** METHODS **********
    public: 
        void setGeometry ( const QRect & g );
        
    protected: 
        
    private:

    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:



};

#endif // ONETOONEASSICIATIONWIDGET_H
