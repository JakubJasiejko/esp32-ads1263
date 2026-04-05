/**
 * @file spi.c
 * @brief Legacy SPI helper implementation used by the ADS1263 driver.
 */

#include "spi.h"
#include <string.h>

spi_device_handle_t spi_handles[MAX_SPI_DEVICES];


/**
 * @brief Initializes the SPI host with the selected MOSI, MISO, and SCLK pins.
 */
uint8_t spi_init(gpio_num_t mosi, gpio_num_t miso, gpio_num_t sclk) {
    spi_bus_config_t buscfg = {
        .mosi_io_num = mosi,
        .miso_io_num = miso,
        .sclk_io_num = sclk,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 64,
    };

    return (spi_bus_initialize(LEGACY_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO) == ESP_OK) ? 0x00 : 0xFF;
}

/**
 * @brief Adds a new SPI device to the legacy SPI host.
 */
uint8_t addSpiDevice(gpio_num_t cs_pin, int index) {
    if (index >= MAX_SPI_DEVICES) return 0xFF;

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = LEGACY_SPI_CLK_SPEED,
        .mode = 0,
        .spics_io_num = cs_pin,
        .queue_size = 1,
    };

    return (spi_bus_add_device(LEGACY_SPI_HOST, &devcfg, &spi_handles[index]) == ESP_OK) ? 0x00 : 0xFF;
}

/**
 * @brief Sends a single byte over SPI.
 */
uint8_t spi_write(uint8_t* data, int index) {
    spi_transaction_t t = {
        .length = 8 * sizeof(uint8_t),  // One byte
        .tx_buffer = data,
        .rx_buffer = NULL,
    };
    return (spi_device_transmit(spi_handles[index], &t) == ESP_OK) ? 0x00 : 0xFF;
}

/**
 * @brief Sends three bytes over SPI.
 */
uint8_t spi_write24(uint8_t* data, int index) {
    spi_transaction_t t = {
        .length = 24,
        .tx_buffer = data,
        .rx_buffer = NULL,
    };
    return (spi_device_transmit(spi_handles[index], &t) == ESP_OK) ? 0x00 : 0xFF;
}

/**
 * @brief Sends two bytes over SPI.
 */
uint8_t spi_write16(uint8_t* data, int index) {
    spi_transaction_t t = {
        .length = 16,
        .tx_buffer = data,
        .rx_buffer = NULL,
    };
    return (spi_device_transmit(spi_handles[index], &t) == ESP_OK) ? 0x00 : 0xFF;
}

/**
 * @brief Performs a full-duplex SPI transfer.
 */
uint8_t spi_read(uint8_t* tx_data, uint8_t* rx_data, size_t length, int index) {
    spi_transaction_t t = {
        .length = length * 8,
        .tx_buffer = tx_data,
        .rx_buffer = rx_data,
    };

    return (spi_device_transmit(spi_handles[index], &t) == ESP_OK) ? 0x00 : 0xFF;
}

/**
 * @brief Reads an ADS1263 register using the RREG command format.
 */
uint32_t ads1263_readReg(uint8_t reg, uint8_t index) {
    uint8_t tx[3] = { ADS1263_RREG | reg , 0x00, 0xFF };
    uint8_t rx[3] = { 0 };

    if (spi_read(tx, rx, 3, index) != 0x00)
        return 0xFFFFFFFF;

    uint32_t value = ((uint32_t)rx[0] << 16) | ((uint32_t)rx[1] << 8) | rx[2];
    return value;
}

/**
 * @brief Writes one ADS1263 register using WREG.
 */
uint8_t ads1263_writeReg(uint8_t reg, uint8_t data, int index) {
    uint8_t cmd[3];
    cmd[0] = ADS1263_WREG | reg;  // WREG command with register address
    cmd[1] = 0x00;                // One data byte follows
    cmd[2] = data;

    return spi_write24(cmd, index);
}


/**
 * @brief Sends a command byte to the ADS1263.
 */
uint8_t ads1263_sendCommand(uint8_t cmd, int index) {
    return spi_write(&cmd, index);  // Pass the command byte by address
}

/**
 * @brief Removes all devices and frees the legacy SPI bus.
 */
uint8_t spi_deinit(void) {
    // Remove all registered devices.
    for (int i = 0; i < MAX_SPI_DEVICES; i++) {
        if (spi_handles[i] != NULL) {
            spi_bus_remove_device(spi_handles[i]);
            spi_handles[i] = NULL;
        }
    }

    // Free the SPI bus.
    return (spi_bus_free(LEGACY_SPI_HOST) == ESP_OK) ? 0x00 : 0xFF;
}

