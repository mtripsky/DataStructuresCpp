#!/bin/bash

# rm -rf build
# echo build folder removed

# cmake -H. -Bbuild  
# cmake --build build

# ./build/tests/dsc_tests


##### NEW STRUCTURE ####
cd dsc_lib
rm -rf build
mkdir build && cd $_

# Build library in Debug
echo Build dsc library in DEBUG
rm -rf ../install/* && rm -rf ./* && cmake -DCMAKE_BUILD_TYPE=Debug ..

# Install library in Debug
echo Installing library in DEBUG
cmake --build . --target install

# Build library in Release
echo Build CLogger library in RELEASE
rm -rf ./* && cmake -DCMAKE_BUILD_TYPE=Release ..

# Install library in Release
echo Installing library in RELEASE
cmake --build . --target install

tree ../install/

# Running test application
cd ../../dsc_lib_tests
rm -rf build
echo Build test-project to test dsc lib in DEBUG
mkdir build && cd $_ && cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
./dsc_tests