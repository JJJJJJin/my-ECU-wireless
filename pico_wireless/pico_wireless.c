#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

// Read register [000] + [5 bit register address]
#define R_REGISTER = 0x00
// Write register [001] + [5 bit register address]
#define W_REGISTER = 0x20
// No Operation
#define NOP = 0xFF 
// Configuration register
#define CONFIG = 0x00


#define NRF24L01_CE_PIN 17
#define NRF24L01_CSN_PIN 18

void nrf24l01_init() {
    // Initialize SPI interface
    spi_init(spi0, 500 * 1000); // 500kHz
    gpio_set_function(19, GPIO_FUNC_SPI); // SCK
    gpio_set_function(20, GPIO_FUNC_SPI); // MOSI
    gpio_set_function(21, GPIO_FUNC_SPI); // MISO

    // Initialize CE and CSN pins
    gpio_init(NRF24L01_CE_PIN);
    gpio_set_dir(NRF24L01_CE_PIN, GPIO_OUT);

    gpio_init(NRF24L01_CSN_PIN);
    gpio_set_dir(NRF24L01_CSN_PIN, GPIO_OUT);

    // Set CSN high to start with
    gpio_put(NRF24L01_CSN_PIN, 1);
}

void nrf24l01_write_register(uint8_t reg, uint8_t value) {
    uint8_t data[2];
    data[0] = reg | 0x20; // Set the R/W bit high for write operations
    data[1] = value;

    gpio_put(NRF24L01_CSN_PIN, 0); // Pull CSN low
    spi_write_blocking(spi0, data, 2); // Write data
    gpio_put(NRF24L01_CSN_PIN, 1); // Pull CSN high
}

uint8_t nrf24l01_read_register(uint8_t reg) {
    uint8_t data[2];
    data[0] = reg & 0x1F; // Set the R/W bit low for read operations

    gpio_put(NRF24L01_CSN_PIN, 0); // Pull CSN low
    spi_write_blocking(spi0, data, 1); // Send register address
    spi_read_blocking(spi0, 0, data, 1); // Read register value
    gpio_put(NRF24L01_CSN_PIN, 1); // Pull CSN high

    return data[0];
}


int main()
{
    nrf24l01_init();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}