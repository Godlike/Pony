#!/bin/sh

set -e

mkdir $BUILD_DIR && cd $BUILD_DIR

cmake .. && make -j${nproc}

ctest -VV
