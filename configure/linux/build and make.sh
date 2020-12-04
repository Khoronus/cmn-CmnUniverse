#!/usr/bin/env bash

# CmnLib
cd ../../CmnLib
mkdir build
cd build
cmake ..
make

# CmnMath
cd ../../CmnMath
mkdir build
cd build
cmake ..
make
