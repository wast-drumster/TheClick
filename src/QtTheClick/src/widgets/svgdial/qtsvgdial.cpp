/*
** Copyright (C) 2012 Sebastian Roeglinger <wast-drumster@gmail.com>
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

#include "qtsvgdial.h"


#include <QtGui/QPainter>
#include <math.h> //for acos and sqrt

//debug
#include <iostream>

QtSvgDial::QtSvgDial(QWidget * parent)
    : QAbstractSlider(parent)
{
    //initialize attriutes
    this->picBackgroundNormal = new QSvgRenderer(this);
    this->picForegroundNormal = new QSvgRenderer(this);
    this->picBackgroundHovered = new QSvgRenderer(this);
    this->picForegroundHovered = new QSvgRenderer(this);
    this->picBackgroundGlow = new QSvgRenderer(this);
    this->picForegroundGlow = new QSvgRenderer(this);
    this->picBackgroundInactive = new QSvgRenderer(this);
    this->picForegroundInactive = new QSvgRenderer(this);
    this->imgTexture = new QImage();
    this->picNub = new QSvgRenderer(this);
    this->picNubSizeToRadiusRatio = 0.3;
    this->picNubRadius = 0.7;
    this->degreeRange = 300.0;
    this->degreeStart = 30.0;
    this->isInactive = false;

    //adapt configuration
    this->setMinimum(0);
    this->setMaximum(100);

    //trigger repaint on enter and leave event
    setAttribute(Qt::WA_Hover, true);
}

QtSvgDial::~QtSvgDial()
{
    if(this->picBackgroundNormal != NULL)
        delete this->picBackgroundNormal;

    if(this->picForegroundNormal != NULL)
        delete this->picForegroundNormal;

    if(this->picBackgroundHovered != NULL)
        delete this->picBackgroundHovered;

    if(this->picForegroundHovered != NULL)
        delete this->picForegroundHovered;

    if(this->picBackgroundGlow != NULL)
        delete this->picBackgroundGlow;

    if(this->picForegroundGlow != NULL)
        delete this->picForegroundGlow;

    if(this->picBackgroundInactive != NULL)
        delete this->picBackgroundInactive;

    if(this->picForegroundInactive != NULL)
        delete this->picForegroundInactive;

    if(this->imgTexture != NULL)
        delete this->imgTexture;

    if(this->picNub != NULL)
        delete this->picNub;
}

void QtSvgDial::setSkin(const QString& skin)
{
    //initialize attributes
    this->m_skin = skin;
    this->shouldGlow = false;

    //load skins
    const QString base = ":/skins/" + skin + '/';
    this->picBackgroundNormal->load(base + "background_normal.svg");
    this->picForegroundNormal->load(base + "foreground_normal.svg");
    this->picBackgroundHovered->load(base + "background_hovered.svg");
    this->picForegroundHovered->load(base + "foreground_hovered.svg");
    this->picBackgroundGlow->load(base + "background_glow.svg");
    this->picForegroundGlow->load(base + "foreground_glow.svg");
    this->picBackgroundInactive->load(base + "background_inactive.svg");
    this->picForegroundInactive->load(base + "foreground_inactive.svg");
    this->imgTexture->load(base + "texture.png");
    this->imgTexture->convertToFormat(QImage::Format_ARGB32_Premultiplied); // calculations should be faster with this transformation
    this->picNub->load(base + "nub.svg");
    
    //update geometry for new sizeHint and repaint
    updateGeometry();
    update();
}

QRect QtSvgDial::dialRect() const
{
    // Keep aspect ratio, always aligned to the left.
    // Later, if a label can be shown to the right
    QSize buttonSize = this->picBackgroundNormal->defaultSize();
    buttonSize.scale(size(), Qt::KeepAspectRatio);
    return QRect(QPoint(0, 0), buttonSize);
}

void QtSvgDial::mousePressEvent(QMouseEvent* event)
{
    QPointF refVector(0, -1); //12 o'clock
    QPointF mouseGlobalVector = event->globalPos() - this->mapToGlobal(QPoint(0,0)) - QPointF(dialRect().width()/2.0, dialRect().height()/2.0);
    double scale = this->maximum() - this->minimum();
    double angle = this->angleVectorsWithOrientation(&refVector, &mouseGlobalVector) / M_PI * 180.0 + 180.0 - this->degreeStart;
    int value = angle / this->degreeRange * scale + this->minimum();

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

void QtSvgDial::mouseMoveEvent(QMouseEvent* event)
{
    QPointF refVector(0, -1); //12 o'clock
    QPointF mouseGlobalVector = event->globalPos() - this->mapToGlobal(QPoint(0,0)) - QPointF(dialRect().width()/2.0, dialRect().height()/2.0);
    double scale = this->maximum() - this->minimum();
    double angle = this->angleVectorsWithOrientation(&refVector, &mouseGlobalVector) / M_PI * 180.0 + 180.0 - this->degreeStart;
    int value = angle / this->degreeRange * scale + this->minimum();

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


void QtSvgDial::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    //determine angle for rotation
    double angle = this->degreeRange / (this->maximum() - this->minimum()) * (this->value() - this->minimum()) + this->degreeStart;

    //draw fore- and background
    if (this->isInactive && this->picBackgroundInactive->isValid())
    {
        this->picBackgroundInactive->render(&painter, dialRect());
        this->picForegroundInactive->render(&painter, dialRect());
    }
    else if (underMouse())
    {
        this->picBackgroundHovered->render(&painter, dialRect());
        this->picForegroundHovered->render(&painter, dialRect());
    }
    else if(this->shouldGlow)
    {
        this->picBackgroundGlow->render(&painter, dialRect());
        this->picForegroundGlow->render(&painter, dialRect());
    }
    else
    {
        this->picBackgroundNormal->render(&painter, dialRect());
        this->picForegroundNormal->render(&painter, dialRect());
    }

    //draw texture
    if(!this->imgTexture->isNull())
    {
        QTransform textureTransform;
        textureTransform.rotate( angle );
        QImage tmpTexture = this->imgTexture->transformed(textureTransform, Qt::FastTransformation);

        double alpha;

        if(fmod(angle, 90.0) < 45.0)
            alpha = fmod(angle, 90.0) / 180.0 * M_PI;
        else
            alpha = (90.0 - fmod(angle, 90.0)) / 180.0 * M_PI;

        double h  = 0.5 * tan(M_PI/4.0 - alpha);
        double x2 = h * tan(alpha);
        double x1 = (0.5 - x2)*(1.0 - cos(alpha));
        double x = x1 + x2;
        QRectF cropRect(tmpTexture.width() * x,
                        tmpTexture.width() * x,
                        tmpTexture.width() - x * tmpTexture.width()*2,
                        tmpTexture.width() - x * tmpTexture.width()*2);

        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    //    painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.drawImage( dialRect() , tmpTexture, cropRect);
    }

    //draw nob
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    double radius = dialRect().width() / 2.0 * this->picNubRadius;
    double nubWidth = radius * this->picNubSizeToRadiusRatio;
    QRectF nubRect(dialRect().width() / 2.0 - radius * sin(angle / 180.0 * M_PI) - nubWidth / 2.0,
                   dialRect().height() / 2.0 + radius * cos(angle / 180.0 * M_PI) - nubWidth / 2.0,
                   nubWidth,
                   nubWidth);
    this->picNub->render(&painter, nubRect);

    //debug
//    painter.drawLine(dialRect().width() / 2.0,
//                     dialRect().height() / 2.0,
//                     dialRect().width() / 2.0 - radius * sin(angle / 180.0 * M_PI),
//                     dialRect().height() / 2.0 + radius * cos(angle / 180.0 * M_PI));
}

QSize QtSvgDial::sizeHint() const
{
    if (this->picBackgroundNormal->isValid()) {
        return this->picBackgroundNormal->defaultSize();
    } else {
        return QAbstractSlider::sizeHint();
    }
}

double QtSvgDial::angleVectors(const QPointF* vector1, const QPointF* vector2) const
{
    double scalarProduct = vector1->x() * vector2->x() + vector1->y() * vector2->y();
    double lengthVector1 = sqrt(pow(vector1->x(), 2) + pow(vector1->y(), 2));
    double lengthVector2 = sqrt(pow(vector2->x(), 2) + pow(vector2->y(), 2));

    return acos(scalarProduct / lengthVector1 / lengthVector2);
}

double QtSvgDial::angleVectorsWithOrientation(const QPointF* vector1, const QPointF* vector2) const
{
    //ref vector (0 / -1) 12 o'clock possition
    QPointF refVector(0.0, -1.0);
    double angle1 = this->angleVectors(&refVector, vector1);
    double angle2 = this->angleVectors(&refVector, vector2);

    if (vector1->x() < 0) angle1 *= -1;
    if (vector2->x() < 0) angle2 *= -1;

    return angle2 - angle1;
}

void QtSvgDial::setShouldGlow(bool v)
{
    this->shouldGlow = v;
    update();
}

void QtSvgDial::setIsInactive(bool v)
{
    this->isInactive = v;
    update();
}
