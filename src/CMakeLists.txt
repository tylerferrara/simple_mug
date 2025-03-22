add_executable(firmware main.cpp)

pico_enable_stdio_usb(firmware 1)

target_link_libraries(firmware pico_stdlib)

pico_add_extra_outputs(firmware)

