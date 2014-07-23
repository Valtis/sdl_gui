#!/bin/sh
set -ex
wget http://github.com/zeux/pugixml/releases/download/v1.4/pugixml-1.4.tar.gz
tar -xzvf pugixml-1.4.tar.gz
cd pugixml-1.4/scripts/
cmake CMakeLists.txt 
make all
sudo cp libpugixml.a /usr/local/lib/libpugixml.a
cd ..
cd src
sudo mkdir /usr/local/include/pugixml
sudo cp pugixml.hpp /usr/local/include/pugixml/pugixml.hpp
sudo cp pugiconfig.hpp /usr/local/include/pugixml/pugiconfig.hpp
cd ..
cd ..
rm -rf pugixml-1.4
