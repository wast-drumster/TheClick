#include($${PWD}/../svgdial/svgdial.pri)
#include($${PWD}/../svgbutton/svgbutton.pri)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
SOURCES += $$PWD/qtsvgdialwithbuttons.cpp
HEADERS += $$PWD/qtsvgdialwithbuttons.h

QT += svg
