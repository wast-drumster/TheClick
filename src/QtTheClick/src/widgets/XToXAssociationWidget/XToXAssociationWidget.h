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

#ifndef XTOXASSICIATIONWIDGET_H
#define XTOXASSICIATIONWIDGET_H

#include <QWidget>
#include <QAbstractButton>
#include "widgets/ScrollListOfWidgets/ScrollListOfWidgets.h"
#include <QList>

class XToXAssociationWidgetException_WidgetNotAvailable : public QtConcurrent::Exception
{
public:
    void raise() const { throw *this; }
    Exception *clone() const { return new XToXAssociationWidgetException_WidgetNotAvailable(*this); }
};

class XToXAssociationWidget : public QWidget
{
    Q_OBJECT

    //********** PRELIMINARY **********
    public:
        struct Association
        {
            QAbstractButton* left;
            QAbstractButton* right;
        };

        enum AssiciationType
        {
            ONE_TO_ONE,
            ONE_TO_N,
            N_TO_ONE
        };

    //********** (DE/CON)STRUCTORS **********
    public:
        XToXAssociationWidget(AssiciationType type, QWidget *parent = 0);
        ~XToXAssociationWidget();

    private:

    //********** ATTRIBUTES **********
    public: 
        //GUI elements
        ScrollListOfWidgets*        leftScrollList;
        ScrollListOfWidgets*        rightScrollList;

    protected: 
        
    private:
        const AssiciationType       type;

        QList<Association>      associationList;
        
    //********** METHODS **********
    public: 
        //overload QWidget
        void setGeometry ( const QRect & g );

        //own stuff
        void pushBackLeftWidget(QAbstractButton* w);
        void pushBackRightWidget(QAbstractButton* w);

        inline QList<Association>::const_iterator begin_Association() const {return this->associationList.begin();}
        inline QList<Association>::const_iterator end_Association() const {return this->associationList.end();}
        void add_Association(QAbstractButton* left, QAbstractButton* right);
        
    protected: 
        
    private:

    //********** SIGNALS **********
    signals:
        void associationChanged();

    //********** SLOTS **********
    private slots:
        void clicked_left();
        void clicked_right();



};

#endif // XTOXASSICIATIONWIDGET_H
