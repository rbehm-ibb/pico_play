# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
#include(pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(spi C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD picoX)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
    main.cpp
    ../ibblib/ledblink.h ../ibblib/ledblink.cpp
    ../ibblib/picoX.h
    ../ibblib/debug.h ../ibblib/debug.cpp
    ../ibblib/gpioinit.h ../ibblib/gpioinit.cpp
)

#target_sources(${PROJECT_NAME} pio_spi.c pio_spi.h )

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME}
    pico_stdlib hardware_spi
)
#pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/spi.pio)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
#pico_enable_stdio_uart(${PROJECT_NAME} 0)
