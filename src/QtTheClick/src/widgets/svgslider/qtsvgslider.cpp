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

#include "qtsvgSlider.h"


#include <QtGui/QPainter>

//debug
#include <iostream>

QtSvgSlider::QtSvgSlider(QWidget * parent)
    : QAbstractSlider(parent)
{
    //initialize attriutes
    this->picBackground = new QSvgRenderer(this);
    this->picIndicator = new QSvgRenderer(this);
//    this->isInactive = false;

    //adapt configuration
    this->setMinimum(0);
    this->setMaximum(100);

    //trigger repaint on enter and leave event
//    setAttribute(Qt::WA_Hover, true);
}

QtSvgSlider::~QtSvgSlider()
{
    if(this->picBackground != NULL)
        delete this->picBackground;

    if(this->picIndicator != NULL)
        delete this->picIndicator;
}

void QtSvgSlider::setSkin(const QString& skin)
{
    //initialize attributes
    this->m_skin = skin;

    //load skins
    const QString base = ":/skins/" + skin + '/';
    this->picBackground->load(base + "background.svg");
    this->picIndicator->load(base + "indicator.svg");

    
    //update geometry for new sizeHint and repaint
    updateGeometry();
    update();
}

void QtSvgSlider::mousePressEvent(QMouseEvent* event)
{
    this->mouseMoveEvent(event);
}

void QtSvgSlider::mouseMoveEvent(QMouseEvent* event)
{
    QPointF mouseGlobalVector = event->globalPos() - this->mapToGlobal(QPoint(0,0));
    double scale = this->maximum() - this->minimum();
    double position = mouseGlobalVector.x() - this->backgroundRect().x();
    int value = ( position / this->backgroundRect().width() ) * scale + this->minimum();

    if(value < this->minimum()) value = this->minimum();
    if(value > this->maximum()) value = this->maximum();

    try
    {
        this->setValue( value );
    }
    catch(...)
    {
        //nothing
    }
}


void QtSvgSlider::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);


    //draw background
//    if (this->isInactive && this->picBackgroundInactive->isValid())
//    {
//        this->picBackgroundInactive->render(&painter, dialRect());
//    }
//    else if (underMouse())
//    {
//        this->picBackgroundHovered->render(&painter, dialRect());
//    }
//    else if(this->shouldGlow)
//    {
//        this->picBackgroundGlow->render(&painter, dialRect());
//    }
//    else
//    {
        this->picBackground->render(&painter, backgroundRect());
//    }


    //draw indicator
    this->picIndicator->render(&painter, indicatorRect());
}

QSize QtSvgSlider::sizeHint() const
{
    if (this->picBackground->isValid()) {
        return this->picBackground->defaultSize();
    } else {
        return QAbstractSlider::sizeHint();
    }
}

QSize QtSvgSlider::indicatorSize() const
{
    // Keep aspect ratio:
    QSize indicatorSize = this->picIndicator->defaultSize();
    indicatorSize.scale(this->size(), Qt::KeepAspectRatio);

    return indicatorSize;
}

QRect QtSvgSlider::indicatorRect() const
{
    // Keep aspect ratio:
    QSize indicatorSize = this->indicatorSize();
    double usedWidth = this->size().width() - indicatorSize.width();
    double scale = this->maximum() - this->minimum();
    double relativePos = ( this->value() - this->minimum() ) / scale;

    return QRect( QPoint(relativePos * usedWidth, 0), indicatorSize );
}

QRect QtSvgSlider::backgroundRect() const
{
    // Keep aspect ratio, always aligned to the left.
    // Later, if a label can be shown to the right
    int indicatorWidth = this->indicatorSize().width();
    return QRect(indicatorWidth/2, 0, this->size().width() - indicatorWidth, this->size().height());
}
