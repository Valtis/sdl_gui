#!/bin/bash
set -ex
make test
./sdl_gui
cd ..
find . -name "*.gcda" -type f -delete
find . -name "*.o" -type f -delete
find . -name "*.gcno" -type f -delete
find . -name "*.gcov" -type f -delete
