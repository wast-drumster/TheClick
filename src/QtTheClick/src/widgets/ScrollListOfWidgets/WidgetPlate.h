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

#ifndef WIDGETPLATE_H
#define WIDGETPLATE_H

#include <QWidget>
#include <list>

class WidgetPlate : public QWidget
{
    Q_OBJECT
    
    //********** (DE/CON)STRUCTORS **********
    public:
        WidgetPlate(QWidget *parent = 0);
        ~WidgetPlate();

    private:

    //********** ATTRIBUTES **********
    public: 
        

    protected: 
        
    private:
        std::list<QWidget*>       widgetList;
        
    //********** METHODS **********
    public: 
        //overload QWidget
        virtual QSize sizeHint () const;
//        void update();
        virtual int heightForWidth (int w) const;
        void setGeometry( const QRect& g );
        void resize( const QSize& s );

        //own stuff
        int size() const {return this->widgetList.size();}
        void addWidget(QWidget* w);


    protected: 
        
    private:

    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:
        //overload QWidget
        virtual void resizeEvent ( QResizeEvent * event );



};

#endif // WIDGETPLATE_H
