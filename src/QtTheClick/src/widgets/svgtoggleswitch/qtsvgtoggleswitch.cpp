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

#include <QtSvg/QSvgRenderer>
#include <QtGui/QPainter>


#include "qtsvgtoggleswitch.h"

QtSvgToggleSwitch::QtSvgToggleSwitch(QWidget * parent) : QAbstractButton(parent)
{
    //initialize attriutes
    m_rendererButtonOffNormal = new QSvgRenderer(this);
    m_rendererButtonOnNormal = new QSvgRenderer(this);
    m_rendererButtonOffHovered = new QSvgRenderer(this);
    m_rendererButtonOnHovered = new QSvgRenderer(this);
    m_rendererButtonOffPressed = new QSvgRenderer(this);
    m_rendererButtonOnPressed = new QSvgRenderer(this);

    //trigger repaint on enter and leave event
    setAttribute(Qt::WA_Hover, true);

    //adapt configuration
    setCheckable(true);
}

QtSvgToggleSwitch::~QtSvgToggleSwitch()
{
}

void QtSvgToggleSwitch::setSkin(const QString& skin)
{
    //initialize attributes
    m_skin = skin;

    //load skins
    const QString base = ":/skins/" + skin + '/';
    m_rendererButtonOffNormal->load(base + "off_normal.svg");
    m_rendererButtonOnNormal->load(base + "on_normal.svg");
    m_rendererButtonOffHovered->load(base + "off_hovered.svg");
    m_rendererButtonOnHovered->load(base + "on_hovered.svg");
    m_rendererButtonOffPressed->load(base + "off_pressed.svg");
    m_rendererButtonOnPressed->load(base + "on_pressed.svg");

    //update geometry for new sizeHint and repaint
    updateGeometry();
    update();
}

QString QtSvgToggleSwitch::skin() const
{
    return m_skin;
}

QRect QtSvgToggleSwitch::buttonRect() const
{
    // Keep aspect ratio, always aligned to the left.
    // Later, if a label can be shown to the right
    QSize buttonSize = m_rendererButtonOffNormal->defaultSize();
    buttonSize.scale(size(), Qt::KeepAspectRatio);
    return QRect(QPoint(0, 0), buttonSize);
}

void QtSvgToggleSwitch::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    if ( !isChecked() )
    {
        if( isDown() )
            m_rendererButtonOffPressed->render(&painter, buttonRect());
        else if( !underMouse() )
            m_rendererButtonOffNormal->render(&painter, buttonRect());
        else
            m_rendererButtonOffHovered->render(&painter, buttonRect());
    }
    else
    {
        if( isDown() )
            m_rendererButtonOnPressed->render(&painter, buttonRect());
        else if( !underMouse() )
            m_rendererButtonOnNormal->render(&painter, buttonRect());
        else
            m_rendererButtonOnHovered->render(&painter, buttonRect());
    }
}

QSize QtSvgToggleSwitch::sizeHint() const
{
    if (m_rendererButtonOnNormal->isValid()) {
        return m_rendererButtonOnNormal->defaultSize();
    } else {
        return QAbstractButton::sizeHint();
    }
}
