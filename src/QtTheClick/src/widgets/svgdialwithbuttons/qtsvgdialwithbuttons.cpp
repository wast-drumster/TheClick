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

#include "widgets/svgdialwithbuttons/qtsvgdialwithbuttons.h"


//debug
#include <iostream>

QtSvgDialWithButtons::QtSvgDialWithButtons(QWidget * parent)
    : QAbstractSlider(parent)
{
    //initialze attributes
    this->defaultSize = QSize(400,100);

    //create and initialize widgets
    this->dial = new QtSvgDial( this );
//    this->dial->setObjectName( QString::fromUtf8("???") );

    this->buttonUp = new QtSvgButton( this );
//    this->buttonUp->setObjectName( QString::fromUtf8("???") );

    this->buttonDown = new QtSvgButton( this );
//    this->buttonDown->setObjectName( QString::fromUtf8("???") );

    this->lineEdit = new QLineEdit( this );
//    this->lineEdit->setObjectName( QString::fromUtf8("???") );
    this->lineEdit->setAlignment(Qt::AlignRight);
    this->lineEdit->setInputMask( QString::fromUtf8("000") );
//    this->lineEditFont.setWeight(75);
    this->lineEditFont.setKerning(true);
    this->lineEdit->setFont(this->lineEditFont);
    dialValueChanged( this->dial->value() );

    //connect singals to slots
    connect(this->buttonUp, SIGNAL(clicked()), this, SLOT(buttonUpClicked()) );
    connect(this->buttonDown, SIGNAL(clicked()), this, SLOT(buttonDownClicked()) );
    connect(this->dial, SIGNAL(valueChanged(int)), this, SLOT(dialValueChanged(int)) );
    connect(this->lineEdit, SIGNAL(editingFinished()), this, SLOT(lineEditEditingFinished()) );

}

QtSvgDialWithButtons::~QtSvgDialWithButtons()
{
}

void QtSvgDialWithButtons::buttonUpClicked()
{
    this->dial->setValue( this->dial->value() + this->dial->singleStep() );
}

void QtSvgDialWithButtons::buttonDownClicked()
{
    this->dial->setValue( this->dial->value() - this->dial->singleStep() );
}

void QtSvgDialWithButtons::dialValueChanged(int value)
{
    this->lineEdit->setText( QString("%1").arg(value,3) );
    emit valueChanged(value);
}

void QtSvgDialWithButtons::lineEditEditingFinished()
{
    this->dial->blockSignals(true);
    this->dial->setValue( this->lineEdit->text().toInt() );
    this->lineEdit->setText( QString("%1").arg(this->dial->value(),3) );
    this->dial->blockSignals(false);
    emit valueChanged(this->dial->value());
}

void QtSvgDialWithButtons::resizeEvent ( QResizeEvent * event )
{
    this->defaultSize = event->size();

    int w = this->defaultSize.width();
    int h = this->defaultSize.height();

    double buttonRatio = (double)(this->buttonUp->sizeHint().width()) / (double)(this->buttonUp->sizeHint().height());
    int wButtons = (int)(buttonRatio * h / 2.0);
    int xButtons = w - wButtons;
    int wText    = w - h - wButtons - 5;
    int xText    = xButtons - wText;

    this->dial->setGeometry( QRect(0,0,h,h) );
    this->buttonUp->setGeometry( QRect(xButtons,0,wButtons,h/2) );
    this->buttonDown->setGeometry( QRect(xButtons,h/2,wButtons,h-h/2) );
    this->lineEdit->setGeometry( QRect(xText,0,wText,h) );

    this->lineEditFont.setPixelSize(0.9 * h);
    this->lineEdit->setFont(this->lineEditFont);
}
