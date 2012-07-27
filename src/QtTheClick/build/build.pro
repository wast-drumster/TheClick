
QT       += core gui

TARGET = TheClick
TEMPLATE = app

include( ../common.pri )
include( ../build.pri )
include( ../src/MainWindow/MainWindow.pri )


#GUI Application
ICON = $$quote($${_PRO_FILE_PWD_}/../rsc/TheClick.icns)

SOURCES += main.cpp

#HEADERS  += \

#FORMS += \
#    MainWindow/TheClickForm.ui

RESOURCES += \
    ../ResourceEx.qrc


