INCLUDEPATH += $$quote($${PWD})
DEPENDPATH += $$quote($${PWD})

FORMS += \
    TheClickForm.ui

SOURCES += \
    MainWindow.cpp \
    SpeedWidget.cpp \
    ClickGeneratorDivisionWidget.cpp \
    ScaleInformation.cpp \
    ClickGeneratorXoYWidget.cpp \
    ClickGeneratorPASWidget.cpp
	
HEADERS += \
    MainWindow.h \
    SpeedWidget.h \
    ClickGeneratorDivisionWidget.h \
    ScaleInformation.h \
    ClickGeneratorXoYWidget.h \
    ClickGeneratorAbstractWidget.h \
    ClickGeneratorPASWidget.h


