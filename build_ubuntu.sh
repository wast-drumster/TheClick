#!/bin/sh

#setup own variables
#MY_DIR=${0%/*}
MY_DIR=$PWD
SETUP_QT_SCRIPT="$MY_DIR/setup_qt_environment.sh"

LIB_BUILD_PATH="$MY_DIR/src/build/libTheClick"
GUI_BUILD_PATH="$MY_DIR/src/build/QtTheClick_release"
LIB_SRC_PATH="$MY_DIR/src/libTheClick"
GUI_SRC_PATH="$MY_DIR/src/QtTheClick"

QT_PRO_PATH="$GUI_SRC_PATH/TheClick.pro"

LIB_PATH="$MY_DIR/src/libraries"



#check dependencies
#qt
#cmake
#gcc
#libraires

#setup Qt environment if the appropriate file exists
if test -x "$SETUP_QT_SCRIPT"; then
  source "$SETUP_QT_SCRIPT"  #Do not run another bash process
  #exec "$SETUP_QT_SCRIPT"
fi

#create build directories
echo
echo "create build directories"
mkdir -p "$LIB_BUILD_PATH"
mkdir -p "$GUI_BUILD_PATH"


#build library
echo
echo "build libTheClick"
cd "$LIB_BUILD_PATH"
cmake "$LIB_SRC_PATH" && make

#link all libraries to one library
echo
echo "link all libraries to one library"
libtool \
 --mode=link \
 gcc -O2 \
 -all-static \
 "$LIB_BUILD_PATH/libTheClick.a" \
 "$LIB_PATH/portaudio/lib/.libs/libportaudio.a" \
 "$LIB_PATH/libsamplerate-0.1.8/src/.libs/libsamplerate.a" \
 "$LIB_PATH/boost_1_50_0/stage/lib/libboost_thread.a" \
 "$LIB_PATH/xerces-c-3.1.1/src/.libs/libxerces-c.a" \
 "$LIB_PATH/libsndfile-1.0.25/src/.libs/libsndfile.a" \
 -o libTheClick_BIG.a 


#build gui
echo
echo "build GUI"
cd "$GUI_BUILD_PATH"
#qmake "$QT_PRO_PATH" -r -spec linux-g++ CONFIG+=release
#make -w

#end script
echo "build process finalized"
cd "$MY_DIR"
