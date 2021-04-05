# cmake -H. -Bbuild
# cmake --build build

cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
project(cpp_data_structures)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(main ${PROJECT_SOURCE_DIR}/tests/main.cpp)
enable_testing ()
