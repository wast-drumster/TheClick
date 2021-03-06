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
DRUMKIT_PATH="$MY_DIR/drumkits"
FINAL_APP_PATH="$GUI_BUILD_PATH/build/TheClick.app"
FINAL_APP_RESOURCES_PATH="$FINAL_APP_PATH/Contents/Resources"

#check dependencies
#qt
#cmake
#gcc
#libraires
#MacOS 10.6 SDK --> show how to install it if it is not available

#setup Qt environment if the appropriate file exists
if test -x "$SETUP_QT_SCRIPT"; then
  source "$SETUP_QT_SCRIPT"  #Do not run another bash process
  #exec "$SETUP_QT_SCRIPT"
fi

#set compiler for CMake (the compiler for qmake is specified with the '-spec' switch)
export CC=clang
export CXX=clang++


#create build directories
echo
echo "create build directories"
mkdir -p "$LIB_BUILD_PATH"
mkdir -p "$GUI_BUILD_PATH"


#build library
echo
echo "build libTheClick"
cd "$LIB_BUILD_PATH"
cmake -D CMAKE_CXX_FLAGS="-arch x86_64" "$LIB_SRC_PATH" && make VERBOSE=1

#link all libraries to one library
#echo
#echo "link all libraries to one library"
#export MACOSX_DEPLOYMENT_TARGET="10.6"
#libtool \
# -static -arch_only x86_64 \
# -L"$LIB_BUILD_PATH" -lTheClick \
# -L"$LIB_PATH/portaudio/lib/.libs" -lportaudio \
# -L"$LIB_PATH/libsamplerate-0.1.8/src/.libs" -lsamplerate \
# -L"$LIB_PATH/boost_1_50_0/stage/lib" -lboost_thread \
# -L"$LIB_PATH/xerces-c-3.1.1/src/.libs" -lxerces-c \
# -L"$LIB_PATH/libsndfile-1.0.25/src/.libs" -lsndfile \
# -framework CoreServices -framework AudioToolbox -framework AudioUnit -framework CoreAudio \
# -o libTheClick_BIG.a 


#build gui
echo
echo "build GUI"
cd "$GUI_BUILD_PATH"
#qmake "$QT_PRO_PATH" -r -spec macx-g++ CONFIG+=release
qmake "$QT_PRO_PATH" -recursive -spec unsupported/macx-clang CONFIG+=release
make -w

#applay macdeployqt on the app
echo
echo "applay macdeployqt on the app"
macdeployqt "$FINAL_APP_PATH"

#copy drumkits into app
echo
echo "copy drumkits into app"
cp -R "$DRUMKIT_PATH" "$FINAL_APP_RESOURCES_PATH"


#end script
echo
echo "build process finalized"
echo
echo "You can find the app at: $FINAL_APP_PATH"
cd "$MY_DIR"

