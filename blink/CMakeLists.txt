cmake_minimum_required(VERSION 3.13)

#set(PICO_BOARD pico)
set(PICO_BOARD picoX)
set(FREERTOS_KERNEL_PATH /home/behm/pico/freertos-pico/FreeRTOS-Kernel)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Pull in FreeRTOS
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(blink main.cpp FreeRTOSConfig.h xtask.h xtask.cpp ../ibblib/debug.h ../ibblib/debug.cpp)

target_include_directories(blink PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# pull in common dependencies
target_link_libraries(blink pico_runtime pico_stdio_usb pico_stdlib FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(blink)
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)


