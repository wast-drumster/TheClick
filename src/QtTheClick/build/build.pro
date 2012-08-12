
QT       += core gui

TARGET = TheClick
TEMPLATE = app

include( ../common.pri )
include( ../build.pri )
include( ../src/MainWindow/MainWindow.pri )


#icon
macx {
    ICON = $$quote($${_PRO_FILE_PWD_}/../rsc/TheClick.icns)
}
win32-g++ {
    RC_FILE = ../Icon_Windows.rc
}

SOURCES += main.cpp

#HEADERS  += \

#FORMS += \
#    MainWindow/TheClickForm.ui

RESOURCES += \
    ../ResourceEx.qrc


