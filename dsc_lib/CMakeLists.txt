cmake_minimum_required(VERSION 3.23)

set(namespace "dsc")
project("dsc"
    VERSION 0.0.1
    DESCRIPTION "Data Structure Library for exercise"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
SET(CMAKE_CXX_FLAGS "-std=c++20")

# SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
if(NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

message(STATUS "Creating library [${PROJECT_NAME}] for top level project [${CMAKE_PROJECT_NAME}]")

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
    src/main.cpp
)

target_include_directories(${PROJECT_NAME}

    # PRIVATE

    # where the library itself will look for its internal headers
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/helpers
    PUBLIC

    # where top-level project will look for the library's public headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

    # where external projects will look for the library's public headers
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# without it public headers won't get installed
file(GLOB public_headers
    "include/*/*.h"
)

# not for MSVC
if(CMAKE_COMPILER_IS_GNUCXX)
    # compile options for this target only
    # treat warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif()

# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# message(STATUS "CMake module path: ${CMAKE_MODULE_PATH}")
include(Installing)
