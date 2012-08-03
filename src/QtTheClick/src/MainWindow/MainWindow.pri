INCLUDEPATH += $$quote($${PWD})
DEPENDPATH += $$quote($${PWD})

FORMS += \
    TheClickForm.ui

SOURCES += \
    MainWindow.cpp \
    SpeedWidget.cpp \
    ScaleInformation.cpp \
    
HEADERS += \
    MainWindow.h \
    SpeedWidget.h \
    ScaleInformation.h \
    
include($${PWD}/SoundElementTab/SoundElementTab.pri)
include($${PWD}/ClickGeneratorTab/ClickGeneratorTab.pri)
