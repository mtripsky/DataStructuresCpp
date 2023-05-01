# cmake -H. -Bbuild
# cmake --build build
cmake_minimum_required(VERSION 3.19)

# set(PROJECT_NAME_EXECUTABLE DataStructuresCPP)
set(TARGET_NAME dsclib)

project(${TARGET_NAME} VERSION 1.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

add_library(${TARGET_NAME} INTERFACE)
target_include_directories(${TARGET_NAME} INTERFACE src/)
install(TARGETS ${TARGET_NAME} ARCHIVE DESTINATION lib/)

add_subdirectory (tests) 