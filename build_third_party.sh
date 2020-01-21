#!/bin/bash
set -o errexit
cd `dirname $0`

pushd third_party
mkdir -p local

pushd googletest
mkdir -p build

pushd build
CC=`which gcc` CXX=`which g++` cmake .. -DCMAKE_INSTALL_PREFIX=../../local
make && make install
popd

rm -rf build
popd

popd
