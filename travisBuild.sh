#!/bin/sh

set -e

mkdir $BUILD_DIR && cd $BUILD_DIR

cmake -DBUILD_SHARED_LIBS=ON .. && make -j${nproc}

ctest -VV
