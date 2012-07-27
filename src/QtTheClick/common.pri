#libTheClick
INCLUDEPATH += "$${PWD}/../libTheClick/include/"
INCLUDEPATH += "$${PWD}/../libraries/portaudio/include/"
INCLUDEPATH += "$${PWD}/../libraries/xerces-c-3.1.1/src/"
INCLUDEPATH += "$${PWD}/../libraries/boost_1_50_0/"
INCLUDEPATH += "$${PWD}/../libraries/libsndfile/src/"
INCLUDEPATH += "$${PWD}/../libraries/libsamplerate-0.1.8/src/"

LIBS += -L"$${PWD}/../build/libTheClick/" -lTheClick_BIG

#LIBS += -L"$${PWD}/../libraries/libsamplerate-0.1.8/src/.libs" -lsamplerate
#LIBS += -L"$${PWD}/../libraries/boost_1_50_0/stage/lib" -lboost_thread
#LIBS += -L"$${PWD}/../libraries/xerces-c-3.1.1/src/.libs" -lxerces-c
#LIBS += -L"$${PWD}/../libraries/portaudio/lib/.libs" -lportaudio
#LIBS += -L"$${PWD}/../libraries/libsndfile/src/.libs" -lsndfile

#MACOSX Frameworks for PortAudio
#QMAKE_LFLAGS += -F/path/to/framework/directory
#QMAKE_LFLAGS += -syslibroot "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk"
LIBS += -framework CoreServices
LIBS += -framework CoreAudio
LIBS += -framework AudioToolbox
LIBS += -framework AudioUnit

#include project stuff
include(./src/widgets/svgtoggleswitch/svgtoggleswitch.pri)
include(./src/widgets/svgbutton/svgbutton.pri)
include(./src/widgets/svgdial/svgdial.pri)
include(./src/widgets/svgdialwithbuttons/svgdialwithbuttons.pri)
include(./src/widgets/ScrollListOfWidgets/ScrollListOfWidgets.pri)
include(./src/widgets/svgslider/svgslider.pri)

INCLUDEPATH += $$quote($${PWD}/src/)
DEPENDPATH += $$quote($${PWD}/src/)
