# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.17)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(display C CXX ASM)
set(PICO_BOARD picoX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

#add_subdirectory(/home/behm/dvlsw/@ibb/pico_play/ibblib)
#target_include_directories(/home/behm/dvlsw/@ibb/pico_play/ibblib)
include_directories(/home/behm/dvlsw/@ibb/pico_play/ibblib)
include_directories(./lib1)

file(GLOB FILESLIB ./lib/*.h .lib/*.cpp)
file(GLOB FILESIBB ../ibblib/*.h ../ibblib/*.cpp)
file(GLOB FILESSRC *.cpp)
file(GLOB FILESH *.h)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
	${FILESSRC}
	${FILESH}
#	${FILESLIB}
	${FILESIBB}
)

#target_sources(test pio_spi.c pio_spi.h )

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	pico_stdio_usb pico_platform pico_util pico_bootsel_via_double_reset
	pico_multicore  hardware_spi
)
# pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/spi.pio)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
#pico_enable_stdio_uart(${PROJECT_NAME} 0)
