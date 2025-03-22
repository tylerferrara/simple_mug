cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

set(PICO_SDK_PATH "${PICO_SDK_PATH}" CACHE PATH "Path to the Pico SDK")
set(PICO_PLATFORM "${PICO_PLATFORM}" CACHE STRING "Platform to build for")

project(mug C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if(NOT PICO_PLATFORM STREQUAL "host")
    pico_sdk_init()
    # Add the firmware directory
    add_subdirectory(src)
endif()

include(ExternalProject)
ExternalProject_Add(tools
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/tools
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    INSTALL_COMMAND ""
    BUILD_ALWAYS 1
)

