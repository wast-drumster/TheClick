PROJECT(TheClick)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#set includes
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/boost_1_50_0)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/portaudio/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/xerces-c-3.1.1/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsndfile-1.0.25/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsamplerate-0.1.8/src)

#set libraries
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsamplerate-0.1.8/src/.libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/boost_1_50_0/stage/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/xerces-c-3.1.1/src/.libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/portaudio/lib/.libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../libraries/libsndfile-1.0.25/src/.libs)


#set project source paths
file(GLOB_RECURSE listOfCMakeLists
    RELATIVE ${PROJECT_SOURCE_DIR}
    "${PROJECT_SOURCE_DIR}/*/CMakeLists.txt"
)

foreach (element ${listOfCMakeLists})
    string(REPLACE "/CMakeLists.txt" "" path ${element})
    message("")
    message("add_subdirectory: " ${path})
    add_subdirectory(${path})
endforeach()


#set compiler
#set(CMAKE_CXX_COMPILER "g++")
#set(CMAKE_CC_COMPILER "gcc")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O4 -ffast-math -fvisibility=hidden")        ## Optimize
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wall")                     ## Warnings
#    set(CMAKE_EXE_LINKER_FLAGS "-s")                                                     ## Strip binary
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O4 -ffast-math -fvisibility=hidden")        ## Optimize
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wall")                     ## Warnings
#    set(CMAKE_EXE_LINKER_FLAGS "-s")                                                     ## Strip binary
endif()

#print configuration
message("")
message("use configuration")
message("cpp-files: " "${src_cpp}")
message("")
message("h-files: " "${src_h}")
message("")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")


ADD_LIBRARY(TheClick STATIC ${src_h} ${src_cpp})
