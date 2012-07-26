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

#include <QtSvg/QSvgRenderer>
#include <QtGui/QPainter>

#include "qtsvgbutton.h"


QtSvgButton::QtSvgButton(QWidget * parent)
    : QAbstractButton(parent)
{
    // trigger repaint on enter and leave event
    setAttribute(Qt::WA_Hover, true);
}

QtSvgButton::~QtSvgButton()
{
}

void QtSvgButton::setSkin(const QString& skin)
{
    m_skin = skin;
    QString base = ":/skins/" + skin + '/';

    // create null size and null pictures
    m_defaultSize = QSize();
    m_normal = QPicture();
    m_hovered = QPicture();
    m_pressed = QPicture();

    QSvgRenderer renderer;
    QPainter painter;

    if (renderer.load(base + "normal.svg")) {
        m_defaultSize = renderer.defaultSize();
        painter.begin(&m_normal);
        renderer.render(&painter, QRectF(0.0, 0.0, 1.0, 1.0));
        painter.end();
    }

    if (renderer.load(base + "pressed.svg")) {
        painter.begin(&m_pressed);
        renderer.render(&painter, QRectF(0.0, 0.0, 1.0, 1.0));
        painter.end();
    }

    if (renderer.load(base + "hovered.svg")) {
        painter.begin(&m_hovered);
        renderer.render(&painter, QRectF(0.0, 0.0, 1.0, 1.0));
        painter.end();
    }

    // update geometry for new sizeHint and repaint
    updateGeometry();
    update();
}

QString QtSvgButton::skin() const
{
    return m_skin;
}

QRect QtSvgButton::buttonRect() const
{
    // Keep aspect ratio:
    QSize buttonSize = m_defaultSize;
    buttonSize.scale(rect().size(), Qt::KeepAspectRatio);

    // Keep the button aligned horizontally centered (like the text):
    int buttonPosX = (rect().width() - buttonSize.width()) / 2;
    if (buttonPosX < 0) buttonPosX = 0;
    buttonPosX += rect().left();

    QPoint buttonPos = QPoint(buttonPosX, 0);

    return QRect(buttonPos, buttonSize);
}

void QtSvgButton::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.scale(buttonRect().width(), buttonRect().height());

    if (isDown()) {
        m_pressed.play(&painter);
    } else if (underMouse()) {
        m_hovered.play(&painter);
    } else {
        m_normal.play(&painter);
    }
}

QSize QtSvgButton::sizeHint() const
{
    if (!m_defaultSize.isEmpty()) {
        return m_defaultSize;
    } else {
        return QSize(100, 24);
    }
}
