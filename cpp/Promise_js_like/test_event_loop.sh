#!/bin/bash
mkdir -p build
cd ./build
cmake ..
make -j 64
echo "====build ok, begin=========="
./test_event_loop

echo "===========done=============="
