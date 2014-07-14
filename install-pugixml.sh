#!/bin/sh
set -ex
wget http://github.com/zeux/pugixml/releases/download/v1.4/pugixml-1.4.tar.gz
tar -xzvf pugixml-1.4.tar.gz
cd pugixml-1.4/scripts/
cmake CMakeLists.txt 
make all
