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

#ifndef XTOXASSOCIATIONABSTRACTWIDGET_H
#define XTOXASSOCIATIONABSTRACTWIDGET_H

#include <QLabel>

#define DISTANCE_X_LEFT        (10)
#define DISTANCE_X_RIGHT       (10)
#define DISTANCE_Y_TOP         (2)
#define DISTANCE_Y_BOTTOM      (2)

class XToXAssociationAbstractWidget : public QWidget
{
    Q_OBJECT
    
    //********** (DE/CON)STRUCTORS **********
    public:
        XToXAssociationAbstractWidget(QWidget *parent = 0);
        virtual ~XToXAssociationAbstractWidget();

    private:

    //********** ATTRIBUTES **********
    public: 
        //GUI elements
        QLabel*    textLabel;

        //own stuff

    protected: 
        
    private:

    //********** METHODS **********
    public:
        //overload QWidget
        virtual QSize sizeHint () const;
        virtual int heightForWidth (int w) const;

        //own stuff
        virtual void setText(const QString& t);
        virtual QString text();
        virtual void setSelected(bool a);
        virtual bool selected();

    protected: 
        
    private:
        
    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:
        //overload QWidget
        virtual void resizeEvent ( QResizeEvent * event );
//        virtual void mousePressOnLabelEvent ( QMouseEvent * ev );


};

#endif // XTOXASSOCIATIONABSTRACTWIDGET_H
