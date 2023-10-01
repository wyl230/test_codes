#!/bin/bash
mkdir -p build
cd ./build
cmake ..
make -j 32
echo "============================="
echo "build ok, program begin..."
echo "============================="
./test

echo "============================="
echo "done"
echo "============================="
