cmake_minimum_required(VERSION 3.21)

project(testDemo)
set(PROJECT_RESOURCES_DIR resources)

set(CMAKE_EXECUTABLE_SUFFIX ".html")

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(testDemo ${SOURCES})
