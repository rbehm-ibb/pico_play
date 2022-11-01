cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(test
    main.cpp
    core1.cpp
    )
pico_enable_stdio_usb(test 1)
#pico_enable_stdio_uart(test 1)
pico_add_extra_outputs(test)
target_link_libraries(test pico_stdlib hardware_uart pico_multicore hardware_timer)
#include ($ENV{PICO_SDK_PATH}/family_add_subdirectory(cdc_msc))
#family_initialize_project(tinyusb_device_examples ${CMAKE_CURRENT_LIST_DIR})
#family_add_subdirectory(cdc_msc)
