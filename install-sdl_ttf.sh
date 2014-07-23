#!/bin/sh
set -ex
wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz
tar -xzvf SDL2_ttf-2.0.12.tar.gz
cd SDL2_ttf-2.0.12/
./configure
make
sudo make install
cd ..
rm -rf SDL2_ttf-2.0.12



