#!/bin/bash
mkdir -p build
cd ./build
cmake ..
make -j 32
echo "buid ok, program begin..."
echo "============================="
./test
