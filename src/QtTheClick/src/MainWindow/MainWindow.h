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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_TheClickForm.h"
#include "libTheClick/libTheClick.h"

#include "MainWindow/SpeedWidget.h"
#include "MainWindow/ClickGeneratorDivisionWidget.h"
#include "MainWindow/ClickGeneratorXoYWidget.h"
#include "MainWindow/ClickGeneratorPASWidget.h"
#include "widgets/ScrollListOfWidgets/ScrollListOfWidgets.h"


#include <QString>
#include <list>


#define MAX_DIAL_VALUE          ((double)100.0)
#define MAX_VOLUMESLIDER_VALUE  ((double)100.0)

#define CLICKGEN_RESET_ID       (-1)

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    //********** (DE/CON)STRUCTORS **********
    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    //********** ATTRIBUTES **********
    private:
        Ui::TheClickForm* theClickForm;

        SpeedWidget*                   speedWidget;
        ClickGeneratorDivisionWidget*  clickGeneratorDivisionWidget;
        ClickGeneratorXoYWidget*       clickGeneratorXoYWidget;
        ClickGeneratorPASWidget*       clickGeneratorPASWidget;
        ScrollListOfWidgets*           clickGeneratorScrollListOfWidgets;

        libTheClick::ClickController*                    clickController;

        std::list<QString*>                              drumkitPathStaticList;

    //********** METHODS **********
    public:
        //overload QWidget
        void resizeEvent(QResizeEvent* event);

        //own stuff

    protected:

    private:

    //********** SIGNALS **********
    signals:

    //********** SLOTS **********
    private slots:
        void shouldResize();

};

#endif // MAINWINDOW_H
