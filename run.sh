#!/bin/bash
# telling CMake to generate Ninja files based in the build directory
# specifying some flags so that, when I build and get a message, I still get the colored text messages of G++
# otherwise I get some hard to read white text
cmake -S . -B build -G Ninja \
  -DCMAKE_CXX_FLAGS="-fdiagnostics-color=always" \
  -DCMAKE_C_FLAGS="-fdiagnostics-color=always"

cmake --build build


