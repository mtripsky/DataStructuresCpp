# cmake -H. -Bbuild
# cmake --build build
cmake_minimum_required(VERSION 3.19)

set(PROJECT_NAME_EXECUTABLE DataStructuresCPP)
project(DataStructuresCPP VERSION 1.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(dsclib INTERFACE)
target_include_directories(dsclib INTERFACE src/ libs/)

add_subdirectory (tests) 