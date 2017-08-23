
cmake_minimum_required(VERSION 3.0)
project(Tests CXX)

include_directories(${PONY_ROOT}/include)

set(SOURCES pony.cpp)
add_executable(tests ${SOURCES})
