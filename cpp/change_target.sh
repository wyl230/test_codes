#!/bin/bash
sed -e 's/main/'$1'/g' CMakeLists.txtcoroutine >CMakeLists.txt
