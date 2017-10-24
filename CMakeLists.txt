# Copyright (C) 2017 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)

project(PonyProject CXX)

option(PONY_BUILD_DOCS "Build Pony project's docs" OFF)
option(PONY_BUILD_TESTS "Build Pony project's tests" ON)
option(BUILD_SHARED_LIBS "Build Pony as shared sets" ON)

set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Werror -pedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3 -O0")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /MP /W3")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

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

if (${PONY_BUILD_DOCS})
    add_subdirectory(docs)
endif()
