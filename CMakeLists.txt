# Copyright (C) 2017 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)

project(PonyProject CXX)

option(PONY_BUILD_TESTS "Build Pony project's tests" ON)

set(PONY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Pony CACHE STRING "Path to Pony project's root")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)

add_subdirectory(${PONY_ROOT})

if (${PONY_BUILD_TESTS})
    set(TEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    set(CATCH_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/external/Catch)
    enable_testing()
    add_subdirectory(${TEST_ROOT})
endif()
