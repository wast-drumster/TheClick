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

#ifndef SVGDIAL_H
#define SVGDIAL_H

#include <QtGui/QAbstractSlider>
#include <QSvgRenderer>
#include <QImage>
#include <QMouseEvent>

class QtSvgDial : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(QString skin READ skin WRITE setSkin)
    //********** (DE/CON)STRUCTORS **********
    public:
        explicit QtSvgDial(QWidget * parent = 0);
        ~QtSvgDial();

    private:

    //********** ATTRIBUTES **********
    public:

    protected:

    private:
        QSize defaultSize;
    
        QSvgRenderer* picBackgroundNormal;
        QSvgRenderer* picForegroundNormal;
        QSvgRenderer* picBackgroundHovered;
        QSvgRenderer* picForegroundHovered;
        QSvgRenderer* picBackgroundGlow;
        QSvgRenderer* picForegroundGlow;
        QSvgRenderer* picBackgroundInactive;
        QSvgRenderer* picForegroundInactive;
        QImage*       imgTexture;
        QSvgRenderer* picNub;
        double        picNubSizeToRadiusRatio;
        double        picNubRadius;

        double degreeRange;
        double degreeStart;

        QString m_skin;
        bool shouldGlow;
        bool isInactive;

    //********** METHODS **********
    public:
        QSize sizeHint() const;
        void setSkin(const QString& skin);
        inline QString skin() const {return this->m_skin;}

        void setShouldGlow(bool v);
        bool getShouldGlow() const {return this->shouldGlow;}

        void setIsInactive(bool v);
        bool getIsInactive() const {return this->isInactive;}

        void setNubSizeToRadiusRatio(double r) {this->picNubSizeToRadiusRatio = r;}
        void setNubRadius(double r) {this->picNubRadius = r;}

    protected:
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent(QMouseEvent* event);
//        virtual void wheelEvent(QWheelEvent* event);
        virtual void paintEvent(QPaintEvent* event);

    private:
        QRect dialRect() const;
        double angleVectors(const QPointF* vector1, const QPointF* vector2) const;
        double angleVectorsWithOrientation(const QPointF* vector1, const QPointF* vector2) const;


    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:



};

#endif // SVGDIAL_H
