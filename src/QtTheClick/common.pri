#libTheClick
INCLUDEPATH += "$${PWD}/../libTheClick/include/"
INCLUDEPATH += "$${PWD}/../libTheClick/src/libTheClick/" #to be able to see source code at debugging
INCLUDEPATH += "$${PWD}/../libraries/portaudio/include/"
INCLUDEPATH += "$${PWD}/../libraries/xerces-c-3.1.1/src/"
INCLUDEPATH += "$${PWD}/../libraries/boost_1_50_0/"
INCLUDEPATH += "$${PWD}/../libraries/libsndfile-1.0.25/src/"
INCLUDEPATH += "$${PWD}/../libraries/libsamplerate-0.1.8/src/"

LIBS += -L"$${PWD}/../build/libTheClick/" "-lTheClick"
#LIBS += -L"$${PWD}/../build/libTheClick/" -lTheClick_BIG

LIBS += -L"$${PWD}/../libraries/libsamplerate-0.1.8/src/.libs" -lsamplerate
LIBS += -L"$${PWD}/../libraries/boost_1_50_0/stage/lib" -lboost_thread -lboost_system
LIBS += -L"$${PWD}/../libraries/xerces-c-3.1.1/src/.libs" -lxerces-c
LIBS += -L"$${PWD}/../libraries/portaudio/lib/.libs" -lportaudio
LIBS += -L"$${PWD}/../libraries/libsndfile-1.0.25/src/.libs" -lsndfile

#Links Frameworks/Libraries for PortAudio
macx {
    #QMAKE_LFLAGS += -F/path/to/framework/directory
    LIBS += -framework CoreServices
    LIBS += -framework CoreAudio
    LIBS += -framework AudioToolbox
    LIBS += -framework AudioUnit
}

#do not use 'unix' because it is 'macx' is also a unix ;)
linux-g++ {
    LIBS += -lrt
    #LIBS += -lasound   #time of stream is not working --> use jack
    LIBS += -ljack
    LIBS += -lpthread
}

win32-g++ {
    #LIBS += -lboost_chrono
	#LIBS += -lpthread
}

#set compiler lags
unix {
    QMAKE_CXXFLAGS_RELEASE = -O4
    QMAKE_CXXFLAGS = -ffast-math 
    QMAKE_CXXFLAGS += -fvisibility=hidden
    QMAKE_CXXFLAGS += -Wold-style-cast
    QMAKE_CXXFLAGS += -Wall
}

#include project stuff
include(./src/widgets/svgtoggleswitch/svgtoggleswitch.pri)
include(./src/widgets/svgbutton/svgbutton.pri)
include(./src/widgets/svgdial/svgdial.pri)
include(./src/widgets/svgdialwithbuttons/svgdialwithbuttons.pri)
include(./src/widgets/ScrollListOfWidgets/ScrollListOfWidgets.pri)
include(./src/widgets/svgslider/svgslider.pri)
include(./src/widgets/XToXAssociationWidget/XToXAssociationWidget.pri)

INCLUDEPATH += $$quote($${PWD}/src/)
DEPENDPATH += $$quote($${PWD}/src/)
