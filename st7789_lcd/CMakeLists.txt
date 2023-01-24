cmake_minimum_required(VERSION 3.20)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
set(PICO_BOARD picoX)
pico_sdk_init()
project(st7789 VERSION 0.1.1 LANGUAGES C CXX ASM)

add_executable(${PROJECT_NAME}
    main.cpp
#    raspberry_256x256_rgb565.h
    st7789_lcd.pio
    st7789.h st7789.cpp
    ibblib/picoX.h
    ibblib/debug.h ibblib/debug.cpp
    ibblib/ledblink.h ibblib/ledblink.cpp
    ibblib/gpioinit.h ibblib/gpioinit.cpp
    point.h point.cpp
    ibfont.h ibfont.cpp
    propfont.h propfont.cpp
    font8x16.h font8x16.cpp
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/st7789_lcd.pio)

#target_sources(${PROJECT_NAME} PRIVATE st7789_lcd.c)

target_link_libraries(${PROJECT_NAME} PRIVATE pico_stdlib hardware_pio hardware_interp hardware_adc)
pico_add_extra_outputs(${PROJECT_NAME})

# add url via pico_set_program_url
#example_auto_set_url(pio_st7789_lcd)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

