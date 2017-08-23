
cmake_minimum_required(VERSION 3.0)
project(Pony CXX)

option(PONY_BUILD_DOCS "Build Pony project's docs" OFF)
option(PONY_BUILD_TESTS "Build Pony project's tests" ON)

set(PONY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "Path to Pony project's root")

if (${PONY_BUILD_TESTS})
    add_subdirectory(tests)
endif()
