#!/bin/bash

rm -rf bin
echo bin folder removed
rm -rf build
echo build folder removed

cmake -H. -Bbuild  
cmake --build build


./bin/main
