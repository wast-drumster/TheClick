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

#include "MainWindow/SoundConfigurationTab/XToXAssociationAbstractWidget.h"
#include "MainWindow/ScaleInformation.h"

//debug
#include <iostream>

//***************************************
//********** (DE/CON)STRUCTORS **********
//***************************************
XToXAssociationAbstractWidget::XToXAssociationAbstractWidget(QWidget *parent)
    : QWidget(parent)
{
    //initialize attributes


    //create and initialize widgets
    this->textLabel = new QLabel( this );
    this->textLabel->setObjectName( QString::fromUtf8("textLabel") );
    QFont fontTextLabel;
    fontTextLabel.setPointSize(10);
    fontTextLabel.setBold(true);
    fontTextLabel.setWeight(75);
    fontTextLabel.setKerning(true);
    this->textLabel->setFont(fontTextLabel);
    this->textLabel->setScaledContents(false);
    this->textLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    this->textLabel->setText( QString::fromUtf8("???") );
}

XToXAssociationAbstractWidget::~XToXAssociationAbstractWidget()
{

}

//*****************************
//********** METHODS **********
//*****************************
QSize XToXAssociationAbstractWidget::sizeHint() const
{
    QSize ret(this->parentWidget()->parentWidget()->geometry().width(), this->heightForWidth(0) );

//    std::cout << "XToXAssociationAbstractWidget::sizeHint(); w: "  << ret.width() << "   h: " << ret.height() << std::endl;
    return ret;
}

int XToXAssociationAbstractWidget::heightForWidth(int w) const
{
    int ret = ScaleInformation::getInstance()->getPixelSizeNormalText() + DISTANCE_Y_BOTTOM + DISTANCE_Y_TOP;

//    std::cout << "XToXAssociationAbstractWidget::heightForWidth(); w: " << w << "   h: " << ret << std::endl;
    return ret;
}

void XToXAssociationAbstractWidget::setText(const QString& t)
{
    this->textLabel->setText(t);
}

QString XToXAssociationAbstractWidget::text()
{
    return this->textLabel->text();
}

void XToXAssociationAbstractWidget::setSelected(bool a)
{
    this->setAutoFillBackground(a);
}

bool XToXAssociationAbstractWidget::selected()
{
    return this->autoFillBackground();
}

//*****************************
//********** SIGNALS **********
//*****************************

//*****************************
//*********** SLOTS ***********
//*****************************
void XToXAssociationAbstractWidget::resizeEvent ( QResizeEvent * event )
{
    //general stuff
    int textPixelSize = ScaleInformation::getInstance()->getPixelSizeNormalText();
    QFont fontNextElement;

    //place widgets
    this->textLabel->setGeometry( QRect(DISTANCE_X_LEFT, 0, this->size().width() - DISTANCE_X_LEFT - DISTANCE_X_RIGHT, this->size().height()) );
    fontNextElement = this->textLabel->font();
    fontNextElement.setPixelSize( textPixelSize );
    this->textLabel->setFont( fontNextElement );

    //update
    update();
}

