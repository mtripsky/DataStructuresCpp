#!/bin/bash

rm -rf build
echo build folder removed

cmake -H. -Bbuild  
cmake --build build

./build/tests/dsc_tests