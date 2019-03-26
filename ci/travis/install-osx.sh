#!/usr/bin/env bash
brew update

CMAKE_VERSION=3.13.4
CMAKE_VERSION_DIR=v3.13

CMAKE_OS=Darwin-x86_64
CMAKE_TAR=cmake-${CMAKE_VERSION}-${CMAKE_OS}.tar.gz
CMAKE_URL=http://www.cmake.org/files/${CMAKE_VERSION_DIR}/${CMAKE_TAR}
CMAKE_DIR=$(pwd)/cmake-${CMAKE_VERSION}

wget ${CMAKE_URL}
mkdir -p ${CMAKE_DIR}
tar --strip-components=1 -xzf ${CMAKE_TAR} -C ${CMAKE_DIR}
export PATH=${CMAKE_DIR}/CMake.app/Contents/bin:${PATH}
cmake --version
