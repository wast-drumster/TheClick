PROJECT(TheClickTest)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libTheClick/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/boost_1_50_0)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/portaudio/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/xerces-c-3.1.1/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsndfile-1.0.25/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsamplerate-0.1.8/src)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsamplerate-0.1.8/src/.libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/boost_1_50_0/stage/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/xerces-c-3.1.1/src/.libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/portaudio/lib/.libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsndfile-1.0.25/src/.libs)

ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/libTheClick)

#SET( src_h
#
#)

SET( src_cpp
	./main.cpp
)

IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "-g")
    #SET(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
ENDIF()

ADD_EXECUTABLE(TheClickTest ${src_cpp})
#TARGET_LINK_LIBRARIES(TheClickTest TheClick pthread boost_thread boost_system portaudio xerces-c sndfile samplerate rt asound jack)
TARGET_LINK_LIBRARIES(TheClickTest TheClick pthread boost_thread boost_system portaudio xerces-c sndfile samplerate rt jack)
