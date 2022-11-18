cmake_minimum_required(VERSION 3.21)

project(testDemo)
set(PROJECT_RESOURCES_DIR resources)
if (${EMSCRIPTEN})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 --js-library ${CMAKE_CURRENT_SOURCE_DIR}/jslibs/pkg.js")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(testDemo ${SOURCES})
