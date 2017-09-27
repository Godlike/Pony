# Copyright (C) 2017 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)

project(PonyTests)

include_directories(
    ${PONY_ROOT}/include
    ${CATCH_ROOT}/include
)

function(pony_add_test)
    set(options)
    set(oneValueArgs NAME TEST_NAME)
    set(multiValueArgs SOURCE ARGS DEPENDS)
    cmake_parse_arguments(
        pony_add_test
        "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN}
    )

    add_executable(
        ${pony_add_test_NAME}
        ${pony_add_test_SOURCE}
    )

    if (pony_add_test_DEPENDS)
        target_link_libraries(${pony_add_test_NAME} ${pony_add_test_DEPENDS})
    endif()

    add_test(
        NAME ${pony_add_test_TEST_NAME}
        COMMAND ${pony_add_test_NAME} ${pony_add_test_ARGS}
    )
endfunction()

pony_add_test(NAME AddressTest
    TEST_NAME Address
    SOURCE AddressTest.cpp
    DEPENDS ${PONY_LIB}
)

pony_add_test(NAME SocketTest
    TEST_NAME Socket
    SOURCE SocketTest.cpp
    DEPENDS ${PONY_LIB}
)
