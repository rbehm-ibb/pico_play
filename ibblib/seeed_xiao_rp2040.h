/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef _BOARDS_SEEED_XIAO_RP2040_H
#define _BOARDS_SEEED_XIAO_RP2040_H

// For board detection
#define SEEED_XIAO_RP2040

// On some samples, the xosc can take longer to stabilize than is usual
#ifndef PICO_XOSC_STARTUP_DELAY_MULTIPLIER
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64
#endif

//------------- UART -------------//
#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 0
#endif

#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 0
#endif

#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 1
#endif

//------------- LED -------------//
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 25
#define PICO_LED_B 25
#define PICO_LED_G 16
#define PICO_LED_R 17
#endif

#ifndef PICO_DEFAULT_LED_PIN_INVERTED
#define PICO_DEFAULT_LED_PIN_INVERTED 1
#endif

#ifndef PICO_DEFAULT_WS2812_PIN
#define PICO_DEFAULT_WS2812_PIN 12
#endif

#ifndef PICO_DEFAULT_WS2812_POWER_PIN
#define PICO_DEFAULT_WS2812_POWER_PIN 11
#endif

#ifndef PICO_PINS
#define PICO_PINS
// analog 1..4
#define PICO_A0 26
#define PICO_A1 27
#define PICO_A2 28
#define PICO_A3 29

// GPIO
#define PICO_D0 26
#define PICO_D1 27
#define PICO_D2 28
#define PICO_D3 29
#define PICO_D4 6
#define PICO_D5 7
#define PICO_D6 0
#define PICO_D7 1
#define PICO_D8 2
#define PICO_D9 4
#define PICO_D10 3
#endif

//------------- I2C -------------//
#ifndef PICO_DEFAULT_I2C
#define PICO_DEFAULT_I2C 1
#endif

#ifndef PICO_DEFAULT_I2C_SDA_PIN
#define PICO_DEFAULT_I2C_SDA_PIN 6
#endif

#ifndef PICO_DEFAULT_I2C_SCL_PIN
#define PICO_DEFAULT_I2C_SCL_PIN 7
#endif

//------------- SPI -------------//
#ifndef PICO_DEFAULT_SPI
#define PICO_DEFAULT_SPI 0
#endif

#ifndef PICO_DEFAULT_SPI_TX_PIN
#define PICO_DEFAULT_SPI_TX_PIN 3
#endif

#ifndef PICO_DEFAULT_SPI_RX_PIN
#define PICO_DEFAULT_SPI_RX_PIN 4
#endif

#ifndef PICO_DEFAULT_SPI_SCK_PIN
#define PICO_DEFAULT_SPI_SCK_PIN 2
#endif

//------------- FLASH -------------//

#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1

#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif

#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (2 * 1024 * 1024)
#endif

// All boards have B1 RP2040
#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 0
#endif

#endif
