# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.17)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(mpu6050 C CXX ASM)
set(PICO_BOARD picoX)
#set(PICO_BOARD seeed_xiao_rp2040)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

include_directories(../ibblib)
#file(GLOB FILESIBB ../ibblib/*.h ../ibblib/*.cpp)
file(GLOB FILESSRC *.cpp *.c)
file(GLOB FILESH *.h)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
	mpu6050_i2c.c
#	${FILESSRC}
#	${FILESH}
#	${FILESIBB}
#	/home/behm/pico/pico-sdk/src/boards/include/boards/seeed_xiao_rp2040.h
)

#target_sources(${PROJECT_NAME} ${FILESSRC} ${FILESH} )

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	pico_mem_ops
	hardware_i2c
)
# pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/spi.pio)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
#pico_enable_stdio_uart(${PROJECT_NAME} 0)
