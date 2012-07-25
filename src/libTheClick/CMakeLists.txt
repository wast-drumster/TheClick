PROJECT(TheClick)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/boost_1_49_0)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/portaudio/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/xerces-c-3.1.1/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsndfile/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsamplerate-0.1.8/src)


LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsamplerate-0.1.8/src/.libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/boost_1_49_0/bin.v2/libs/thread/build/darwin-4.2.1/release/address-model-64/architecture-x86/link-static/threading-multi)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/xerces-c-3.1.1/src/.libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/portaudio/lib/.libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsndfile/src/.libs)



SET( src_h
	./include/libTheClick/ClickConfiguration.h
	./include/libTheClick/ClickController.h
	./include/libTheClick/ClickGenerator/ClickGenerator_DivisionSubdivision.h
	./include/libTheClick/ClickGenerator/ClickGenerator_DummyBeatCount.h
	./include/libTheClick/ClickGenerator/ClickGenerator_Interface.h
	./include/libTheClick/ClickGenerator/ClickGenerator_Rudiments.h
	./include/libTheClick/ClickGenerator/ClickGenerator_XoverY.h
	./include/libTheClick/ClickGenerator/ClickGeneratorElement.h
	./include/libTheClick/definitions.h
	./include/libTheClick/DrumKit/DrumKit.h
	./include/libTheClick/DrumKit/Instrument.h
	./include/libTheClick/DrumKit/InstrumentLayer.h
	./include/libTheClick/helper/Xerces/DOMTreeErrorHandler.h
	./include/libTheClick/helper/Xerces/StrX.h
	./include/libTheClick/libTheClick.h
	./include/libTheClick/Sound/Sound_Interface.h
	./include/libTheClick/Sound/Sound_Mono.h
	./include/libTheClick/Sound/Sound_Stereo.h
	./include/libTheClick/Sound/SoundElement.h
	./include/libTheClick/SoundBase.h
	./include/libTheClick/types.h
)

SET( src_cpp
	./src/libTheClick/ClickConfiguration.cc
	./src/libTheClick/ClickController.cc
	./src/libTheClick/ClickGenerator/ClickGenerator_DivisionSubdivision.cc
	./src/libTheClick/ClickGenerator/ClickGenerator_DummyBeatCount.cc
	./src/libTheClick/ClickGenerator/ClickGenerator_Rudiments.cc
	./src/libTheClick/ClickGenerator/ClickGenerator_XoverY.cc
	./src/libTheClick/ClickGenerator/ClickGeneratorElement.cc
	./src/libTheClick/DrumKit/DrumKit.cc
	./src/libTheClick/DrumKit/Instrument.cc
	./src/libTheClick/DrumKit/InstrumentLayer.cc
	./src/libTheClick/helper/Xerces/DOMTreeErrorHandler.cc
	./src/libTheClick/helper/Xerces/StrX.cc
	./src/libTheClick/Sound/Sound_Interface.cc
	./src/libTheClick/Sound/Sound_Mono.cc
	./src/libTheClick/Sound/Sound_Stereo.cc
	./src/libTheClick/Sound/SoundElement.cc
	./src/libTheClick/SoundBase.cc
)

#SET( extra_libs
#	libxerces-c.a
#	libsndfile.a
#	libportaudio.a
#	libboost_thread.a
#	libsamplerate.a
#)

#IF(APPLE)
#	SET(CMAKE_EXE_LINKER_FLAGS "-framework CoreServices -framework CoreAudio -framework AudioToolbox -framework AudioUnit")
#ENDIF (APPLE)

#SET(CMAKE_OSX_ARCHITECTURES x86_64)
#SET(MACOSX_DEPLOYMENT_TARGET 10.6)

IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "-O3")        ## Optimize
    SET(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
ENDIF()

ADD_LIBRARY(TheClick STATIC ${src_h} ${src_cpp})

#SET_TARGET_PROPERTIES(TheClick PROPERTIES STATIC_LIBRARY_FLAGS
#	${PROJECT_SOURCE_DIR}/../libraries/libsamplerate-0.1.8/src/.libs/libsamplerate.a
#	${PROJECT_SOURCE_DIR}/../libraries/boost_1_49_0/bin.v2/libs/thread/build/darwin-4.2.1/release/address-model-64/architecture-x86/link-static/threading-multi/libboost_thread.a
#	${PROJECT_SOURCE_DIR}/../libraries/xerces-c-3.1.1/src/.libs/libxerces-c.a
#	${PROJECT_SOURCE_DIR}/../libraries/portaudio/lib/.libs/libportaudio.a
#	${PROJECT_SOURCE_DIR}/../libraries/libsndfile/src/.libs/libsndfile.a
#)
