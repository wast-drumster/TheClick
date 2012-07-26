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

#ifndef SVGSLIDER_H
#define SVGSLIDER_H

#include <QtGui/QAbstractSlider>
#include <QSvgRenderer>
#include <QMouseEvent>

class QtSvgSlider : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(QString skin READ skin WRITE setSkin)
    //********** (DE/CON)STRUCTORS **********
    public:
        explicit QtSvgSlider(QWidget * parent = 0);
        ~QtSvgSlider();

    private:

    //********** ATTRIBUTES **********
    public:

    protected:

    private:
        QSize defaultSize;
    
        QSvgRenderer* picBackground;
        QSvgRenderer* picIndicator;
        
        QString m_skin;
        bool shouldGlow;
        // bool isInactive;

        QPoint mousePressGlobalPosition;
    
    //********** METHODS **********
    public:
        QSize sizeHint() const;
        void setSkin(const QString& skin);
        inline QString skin() const {return this->m_skin;}

        // void setIsInactive(bool v);
        // bool getIsInactive() const {return this->isInactive;}

    protected:
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent(QMouseEvent* event);
//        virtual void wheelEvent(QWheelEvent* event);
        virtual void paintEvent(QPaintEvent* event);

    private:
        QSize indicatorSize() const;
        QRect indicatorRect() const;
        QRect backgroundRect() const;



    //********** SIGNALS **********
    signals:


    //********** SLOTS **********
    private slots:



};

#endif // SVGSLIDER_H
