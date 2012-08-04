INCLUDEPATH += $$quote($${PWD})
DEPENDPATH += $$quote($${PWD})

FORMS += \
    TheClickForm.ui

SOURCES += \
    ClickGeneratorDivisionWidget.cpp \
    ClickGeneratorXoYWidget.cpp \
    ClickGeneratorPASWidget.cpp

HEADERS += \
    ClickGeneratorDivisionWidget.h \
    ClickGeneratorXoYWidget.h \
    ClickGeneratorAbstractWidget.h \
    ClickGeneratorPASWidget.h \
    ClickGeneratorSoundElementInterface

