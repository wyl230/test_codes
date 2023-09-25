#!/bin/bash
# valgrind --tool=massif ./a.out
g++ test.cpp
./clean.sh
valgrind --tool=massif ./a.out --time-unit=B
./show.sh | less
# ms_print massif.out.12345 # humanize
