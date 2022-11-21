cmake_minimum_required(VERSION 3.21)

project(testDemo)
set(PROJECT_RESOURCES_DIR resources)

macro(append_linker_flags FLAGS)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS}")
endmacro()
if (${EMSCRIPTEN})
    append_linker_flags("-std=c++17")
    append_linker_flags("--js-library ${CMAKE_CURRENT_SOURCE_DIR}/jslibs/pkg.js")
    append_linker_flags("-s \"EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']\"")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(linkFlags "${linkFlags} -lnodefs.js")
endif ()
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(testDemo ${SOURCES})
