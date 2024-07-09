#ifndef PICO_UART_DEBUG_H
#define PICO_UART_DEBUG_H

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/uart.h"

// UART Defines, for debugging only
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define LED_PIN 25

#define LED_TIME_MS 1000

void pico_uart_debug_init();

void pico_uart_debug_printf(char*);

void pico_uart_debug_led_on();

void pico_uart_debug_led_off();

#endif