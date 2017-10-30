#!/bin/sh

set -e

mkdir $BUILD_DIR && cd $BUILD_DIR

cmake -DBUILD_SHARED_LIBS=TRUE .. && make -j${nproc}

ctest -VV
