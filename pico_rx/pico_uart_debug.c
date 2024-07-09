#include <stdio.h>

#include "pico_uart_debug.h"

void pico_uart_debug_init(){
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    //uart_puts(UART_ID, "hello world\r\n");
    return;
}

void pico_uart_debug_printf(char* str){
    //pico_uart_debug_led_on();
    uart_puts(UART_ID, str);
    //pico_uart_debug_led_off();
    return;
}

void pico_uart_debug_led_on(){
    gpio_put(LED_PIN, 1);
    sleep_ms(LED_TIME_MS);
    return;
}

void pico_uart_debug_led_off(){
    gpio_put(LED_PIN, 0);
    sleep_ms(LED_TIME_MS);
    return;
}