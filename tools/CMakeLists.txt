cmake_minimum_required(VERSION 3.12)
project(flash_tools CXX)

# Add the bootsel tool
add_executable(bootsel
    bootsel.cpp
)

# Find libusb using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

target_include_directories(bootsel PRIVATE ${LIBUSB_INCLUDE_DIRS})
target_link_libraries(bootsel PRIVATE ${LIBUSB_LIBRARIES})
target_compile_options(bootsel PRIVATE ${LIBUSB_CFLAGS_OTHER})
set_target_properties(bootsel PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
)

