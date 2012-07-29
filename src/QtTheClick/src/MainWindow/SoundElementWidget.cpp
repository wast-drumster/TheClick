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

#include "MainWindow/SoundElementWidget.h"
#include "MainWindow/ScaleInformation.h"

#include "boost/bind.hpp"

//debug
// #include <iostream>

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
SoundElementWidget::SoundElementWidget(libTheClick::ClickController* clickController, QWidget *parent)
    : QWidget(parent),
      clickController(clickController)
{
    //create and initialize widgets

}

SoundElementWidget::~SoundElementWidget()
{

}

//*****************************
//********** METHODS **********
//*****************************
//*****************************
//********** SIGNALS **********
//*****************************


//*****************************
//*********** SLOTS ***********
//*****************************
void SoundElementWidget::resizeEvent ( QResizeEvent * event )
{
    update();
}

