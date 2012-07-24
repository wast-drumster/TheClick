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

#ifndef QT_SVG_TOGGLE_SWITCH
#define QT_SVG_TOGGLE_SWITCH
#include <QtGui/QAbstractButton>
#include <QtCore/QString>
class QSvgRenderer;

class QtSvgToggleSwitch: public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
    public:
        explicit QtSvgToggleSwitch(QWidget * parent = 0);
        virtual ~QtSvgToggleSwitch();

        void setSkin(const QString& skin);
        QString skin() const;
        virtual QSize sizeHint() const;

    private:
        QRect buttonRect() const;

        QSvgRenderer* m_rendererButtonOffNormal;
        QSvgRenderer* m_rendererButtonOnNormal;
        QSvgRenderer* m_rendererButtonOffHovered;
        QSvgRenderer* m_rendererButtonOnHovered;
        QSvgRenderer* m_rendererButtonOffPressed;
        QSvgRenderer* m_rendererButtonOnPressed;

        QString m_skin;
    protected:
        void paintEvent(QPaintEvent * event);
};

#endif // QT_SVG_TOGGLE_SWITCH
