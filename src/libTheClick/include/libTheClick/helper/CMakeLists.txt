message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

# Find all the input files
file(GLOB src_cpp_tmp
    RELATIVE ${PROJECT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

file(GLOB src_h_tmp
    RELATIVE ${PROJECT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

message("cpp-files: " "${src_cpp_tmp}")
message("h-files: " "${src_h_tmp}")

set(src_cpp ${src_cpp} ${src_cpp_tmp} PARENT_SCOPE)
set(src_h ${src_h} ${src_h_tmp} PARENT_SCOPE)
