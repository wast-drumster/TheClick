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
    
include($${PWD}/SoundConfigurationTab/SoundConfigurationTab.pri)
include($${PWD}/ClickGeneratorTab/ClickGeneratorTab.pri)
