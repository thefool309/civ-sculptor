cmake_minimum_required(VERSION 3.15)
project(mymodule LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.12.0
)

FetchContent_MakeAvailable(pybind11)

file(GLOB SOURCES "src/services/*.cpp")

file(GLOB INCLUDE "src/include/*.h")

pybind11_add_module(civ_module ${SOURCES} ${INCLUDE})

set_target_properties(civ_module PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"  # for Windows .pyd
)
