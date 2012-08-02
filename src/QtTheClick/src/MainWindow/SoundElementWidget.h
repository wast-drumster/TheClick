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

#ifndef SOUNDELEMENTWIDGET_H
#define SOUNDELEMENTWIDGET_H

#include "MainWindow/LabelEnhancedAbstractWidget.h"

class SoundElementWidget : public LabelEnhancedAbstractWidget
{
    Q_OBJECT
    
    //********** (DE/CON)STRUCTORS **********
    public:
        SoundElementWidget(QWidget *parent = 0);
        virtual ~SoundElementWidget();

    private:

    //********** ATTRIBUTES **********
    public: 
        //GUI elements

    protected: 
        
    private:

    //********** METHODS **********
    public:
        //overload QWidget

        //own stuff
        
    protected: 
        
    private:
        
    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:
        //overload QWidget


};

#endif // SOUNDELEMENTWIDGET_H
