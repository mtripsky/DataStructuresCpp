# cmake -H. -Bbuild
# cmake --build build

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
project(cpp-cmake-mines-ci)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(main ${PROJECT_SOURCE_DIR}/tests/main.cpp)
enable_testing ()
