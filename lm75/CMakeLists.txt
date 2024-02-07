# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.17)
# set (PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR} )
# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(lm75 C CXX ASM)
set(PICO_BOARD seeed_xiao_rp2040)

set (LIBHOME $ENV{LIBHOME})


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

add_subdirectory(i2c)
include_directories( ${LIBHOME} )
file(GLOB FILESIBB ${LIBHOME}/*.h ${LIBHOME}/*.cpp)
file(GLOB FILESSRC *.cpp)
file(GLOB FILESH *.h)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
	main.cpp
	${FILESIBB}
	seeed_xiao_rp2040.h
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	pico_mem_ops
	hardware_pio
	i2c
	# hardware_uart hardware_irq
	hardware_i2c
#	pico_multicore
)
# pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/spi.pio)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
#pico_enable_stdio_uart(${PROJECT_NAME} 0)
