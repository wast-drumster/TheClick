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

#ifndef CLICKGENERATORSOUNDWIDGET_H
#define CLICKGENERATORSOUNDWIDGET_H

#include "MainWindow/SoundElementTab/XToXAssociationAbstractWidget.h"
#include "MainWindow/ClickGeneratorTab/ClickGeneratorAbstractWidget.h"

class ClickGeneratorSoundWidget : public XToXAssociationAbstractWidget
{
    Q_OBJECT
    
    //********** (DE/CON)STRUCTORS **********
    public:
        ClickGeneratorSoundWidget(ClickGeneratorAbstractWidget* generator, int32_t soundID, QWidget *parent = 0);
        virtual ~ClickGeneratorSoundWidget();

    private:

    //********** ATTRIBUTES **********
    public: 
        //GUI elements

        //own stuff
        const ClickGeneratorAbstractWidget* generatorClickGeneratorWidget;
        const int32_t                       soundID;

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

#endif // CLICKGENERATORSOUNDWIDGET_H
