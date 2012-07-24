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

#ifndef QT_SVG_BUTTON_H
#define QT_SVG_BUTTON_H

#include <QtGui/QAbstractButton>
#include <QtGui/QPicture>

class QSvgRenderer;

class QtSvgButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
public:
    explicit QtSvgButton(QWidget * parent = 0);
    ~QtSvgButton();

    void setSkin(const QString& skin);
    QString skin() const;

    virtual QSize sizeHint() const;

private:
    QRect buttonRect() const;

    QSize m_defaultSize;
    
    QPicture m_normal;
    QPicture m_hovered;
    QPicture m_pressed;
    QString m_skin;

protected:
    virtual void paintEvent(QPaintEvent* event);
};

#endif // QT_SVG_BUTTON_H
