cmake_minimum_required(VERSION 3.15)
project(CivSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Fetch pybind11
# -----------------------------
include(FetchContent)

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.12.0
)
FetchContent_MakeAvailable(pybind11)

# -----------------------------
# Core library
# -----------------------------
file(GLOB CORE_SOURCES "src/services/*.cpp" "src/include/*.h" )


add_library(civ_core STATIC ${CORE_SOURCES})
target_include_directories(civ_core PUBLIC "src/include")
# -----------------------------
# Python module
# -----------------------------
pybind11_add_module(civ_module "src/python_bindings.cpp")
target_link_libraries(civ_module PRIVATE civ_core pybind11::module)
target_include_directories(civ_module PRIVATE "src/include")

set_target_properties(civ_module PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

# -----------------------------
# Standalone test executable
# -----------------------------
add_executable(run_tests "tests/test.cpp" "tests/test.h")
target_link_libraries(run_tests PRIVATE civ_core)
target_include_directories(run_tests PRIVATE "src/include")
set_target_properties(run_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

# -----------------------------
# Doxygen documentation (optional)
# -----------------------------
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM
    )
endif()