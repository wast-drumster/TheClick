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

#ifndef SVGDIALWITHBUTTONS_H
#define SVGDIALWITHBUTTONS_H


#include "widgets/svgdial/qtsvgdial.h"
#include "widgets/svgbutton/qtsvgbutton.h"
#include "QLineEdit"

class QtSvgDialWithButtons : public QAbstractSlider
{
    Q_OBJECT

    //********** (DE/CON)STRUCTORS **********
    public:
        explicit QtSvgDialWithButtons(QWidget * parent = 0);
        ~QtSvgDialWithButtons();

    private:

    //********** ATTRIBUTES **********
    public:
        QtSvgDial*      dial;
        QtSvgButton*    buttonUp;
        QtSvgButton*    buttonDown;
        QLineEdit*      lineEdit;
        QFont           lineEditFont;

    protected:

    private:
        QSize defaultSize;

    //********** METHODS **********
    public:
        //overload QWidget
        virtual QSize sizeHint () const {return defaultSize;}

        //own stuff
        void setDialSkin(const QString& skin) {this->dial->setSkin(skin);}
        void setButtonUpSkin(const QString& skin) {this->buttonUp->setSkin(skin);}
        void setButtonDownSkin(const QString& skin) {this->buttonDown->setSkin(skin);}

        void setMaximum(int v) {QAbstractSlider::setMaximum(v); this->dial->setMaximum(v);}
        void setMinimum(int v) {QAbstractSlider::setMinimum(v); this->dial->setMinimum(v);}
        int  value() const {return this->dial->value();}
        void setValue(int v) const {this->dial->setValue(v);}

        void setShouldGlow(bool v) {this->dial->setShouldGlow(v);}
        bool getShouldGlow() const {return this->dial->getShouldGlow();}

        void setIsInactive(bool v) {this->dial->setIsInactive(v);}
        bool getIsInactive() const {return this->dial->getIsInactive();}

        void setDefaultSize(QSize s) {this->defaultSize = s;}

    protected:

    private:

    //********** SIGNALS **********
    signals:
        void valueChanged(int value);

    //********** SLOTS **********
    private slots:
        //overload QWidget
        virtual void resizeEvent ( QResizeEvent * event );

        //own stuff
        void buttonUpClicked();
        void buttonDownClicked();
        void dialValueChanged(int value);
        void lineEditEditingFinished();

};

#endif // SVGDIALWITHBUTTONS_H
