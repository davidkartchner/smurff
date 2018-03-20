#!/bin/bash

pushd lib/smurff-cpp/cmake
rm -rf build 
mkdir build
cd build

cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PREFIX -DENABLE_MKL=ON

make -j$CPU_COUNT
make install
popd

pushd python/smurff
$PYTHON setup.py install --with-openmp --single-version-externally-managed --record=record.txt
popd
