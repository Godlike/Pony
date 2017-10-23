# Copyright (C) 2017 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required (VERSION 3.0)

if(NOT DEFINED PONY_NAME)
    set(PONY_NAME "Pony" CACHE STRING "Pony project name.")
endif ()

if(NOT DEFINED PONY_LIB)
    set(PONY_LIB ${PONY_NAME} CACHE STRING "Pony library name.")
endif ()

project(${PONY_LIB})

set(CMAKE_CXX_STANDARD 14)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif (NOT CMAKE_BUILD_TYPE)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -fno-exceptions")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3 -O0")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /MP /W3")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(
    ${PONY_ROOT}/include
)

set(PONY_SOURCES
    source/Address.cpp
    source/Socket.cpp
)

add_library(${PONY_LIB}
    ${PONY_SOURCES}
)

target_link_libraries(${PONY_LIB})
