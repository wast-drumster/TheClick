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

#include <QtGui/QApplication>
#include "MainWindow/MainWindow.h"

#include <QFile>
#include <QObject>
#include <QSplashScreen>
#include <QPixmap>

//debug
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSplashScreen splash( QPixmap(":/skins/splashscreen/TheClick_Splash.png") );
    splash.show();

    //load and set stylesheet
    QFile file(":/rsc/TheClick.qss");
    file.open(QFile::ReadOnly);
    QString StyleSheet = QString::fromUtf8( file.readAll() );

    a.setStyleSheet(StyleSheet);

    //show MainWindows, and thus, start application
    sleep(3);
    w.show();
    splash.finish(&w);
    return a.exec();
}
