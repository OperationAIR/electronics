#!/bin/bash

# Firmware release
set -e # immediately fail on error

# generate version
cd build
echo "Run CMake and Make"
cmake .. && make
echo "Generate FW Version.."
make version

cd ..
echo "Create release folder"
rm -rf release
mkdir release

cp -r .vscode release/.vscode
cp -r cmake release/cmake
cp -r src release/src
cp CHANGELOG release/CHANGELOG
cp CMakeLists.txt release/CMakeLists.txt
cp config.cmake.release release/config.cmake
cp link.ld release/link.ld
cp user_settings.c release/user_settings.c

cd release
echo "Test release build"
mkdir build && cd build
cmake .. && make

echo "Build succeeded"
cd ..
rm -rf build
cd ..
echo "New release available in 'release/'"