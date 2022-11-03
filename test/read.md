# RPi pico

## SDK
  * Works in SuSE with cross compiler from ARM site.
  * needs settings PICO_SDK_PATH
  * PATH to compiler .. bin/
  * set PICO_SDK_PATH in QtC project

## pico
  * multi core working

## cmake setting
  * add_executable(test main.c .. +  other-source)
  * target_link_libraries(test pico_stdlib hardware_uart pico_multicore ++libs)

## misc
  * sdk/common/rp2_common/stdio_usb_descriptor.c has VID+PID

## serial out/USB
  * stdio_init_all(): inits serial0 +  usb
  * stdio_usb_init(); init only usb
  * stdio_usb_connected ot working?

## gpio
   * gpio_init(pin#)
   * gpio_set_dir(pin, dir);
   * gpio_put(pin, val)

## multicore
  * multicore_reset_core1() always before starting core1
  * multicore_launch_core1(fct)

## PIO

## links
  * [Link datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)