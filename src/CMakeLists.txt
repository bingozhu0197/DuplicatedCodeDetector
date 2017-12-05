cmake_minimum_required(VERSION 2.8)

project(DuplicatedCodeDetect)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -std=c++1z")

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR/lib})

file(GLOB clone_detect_SRC
    "*.h"
    "*.cpp"
    )

 include_directories("${PROJECT_SOURCE_DIR}")
 add_executable(clone_detect  ${clone_detect_SRC})
 target_link_libraries(clone_detect stdc++fs)
