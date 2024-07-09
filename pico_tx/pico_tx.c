#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define NRF24L01_CE_PIN 17
#define NRF24L01_CSN_PIN 18

#define NRF24L01_READ_REGISTER 0x00
#define NRF24L01_WRITE_REGISTER 0x20
#define NRF24L01_R_RX_PAYLOAD 0x61
#define NRF24L01_W_TX_PAYLOAD 0xA0
#define NRF24L01_FLUSH_TX 0xE1
#define NRF24L01_FLUSH_RX 0xE2
#define NRF24L01_REUSE_TX_PL 0xE3
#define NRF24L01_NOP 0xFF

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
    data[0] = NRF24L01_WRITE_REGISTER | reg;
    data[1] = value;

    gpio_put(NRF24L01_CSN_PIN, 0); // Pull CSN low
    spi_write_blocking(spi0, data, 2); // Write data
    gpio_put(NRF24L01_CSN_PIN, 1); // Pull CSN high
}

uint8_t nrf24l01_read_register(uint8_t reg) {
    uint8_t data[2];
    data[0] = NRF24L01_READ_REGISTER | reg;

    gpio_put(NRF24L01_CSN_PIN, 0); // Pull CSN low
    spi_write_blocking(spi0, data, 1); // Send register address
    spi_read_blocking(spi0, NRF24L01_NOP, data, 1); // Read register value
    gpio_put(NRF24L01_CSN_PIN, 1); // Pull CSN high

    return data[0];
}

void nrf24l01_write_payload(uint8_t* data, uint8_t length) {
    gpio_put(NRF24L01_CSN_PIN, 0); // Pull CSN low
    uint8_t cmd = NRF24L01_W_TX_PAYLOAD;
    spi_write_blocking(spi0, &cmd, 1); // Send W_TX_PAYLOAD command
    spi_write_blocking(spi0, data, length); // Write payload
    gpio_put(NRF24L01_CSN_PIN, 1); // Pull CSN high
}

void nrf24l01_config_tx_mode() {
    // Set CE low to enter standby mode
    gpio_put(NRF24L01_CE_PIN, 0);

    // Power up and configure for PTX mode
    nrf24l01_write_register(0x00, 0x0A); // CONFIG register: PWR_UP=1, PRIM_RX=0
    nrf24l01_write_register(0x01, 0x3F); // Enable Auto Acknowledgment on all pipes
    nrf24l01_write_register(0x02, 0x03); // Enable RX addresses on pipe 0 and 1
    nrf24l01_write_register(0x04, 0x04); // Set retransmission delay and count
    nrf24l01_write_register(0x06, 0x0F); // RF_SETUP register: Set data rate and power
    nrf24l01_write_register(0x05, 0x02); // RF_CH register: Set frequency channel
}

int main() {
    stdio_init_all();
    nrf24l01_init();
    nrf24l01_config_tx_mode();

    uint8_t tx_data[32] = "Hello, NRF24L01+!";

    gpio_init(25);
    gpio_set_dir(25,GPIO_OUT);

    while (true) {
        gpio_put(25,1);
        sleep_ms(500);
        // Write payload to TX FIFO
        nrf24l01_write_payload(tx_data, sizeof(tx_data));

        // Pulse CE to initiate transmission
        gpio_put(NRF24L01_CE_PIN, 1);
        sleep_us(15); // CE must be held high for at least 10us
        gpio_put(NRF24L01_CE_PIN, 0);

        // Wait for the transmission to complete
        gpio_put(25,0);
        sleep_ms(1000);
    }

    return 0;
}
