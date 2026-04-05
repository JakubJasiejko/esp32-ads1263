/**
 * @file spi.h
 * @brief Legacy SPI helper interface used by the ADS1263 driver.
 */
#ifndef SPI_H
#define SPI_H

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <stdint.h>

#define MAX_SPI_DEVICES 4
#define LEGACY_SPI_HOST      HSPI_HOST
#define LEGACY_SPI_CLK_SPEED 1000000
#define ADS1263_RREG         0x20
#define ADS1263_WREG         0x40

extern spi_device_handle_t spi_handles[MAX_SPI_DEVICES];  // SPI device handles

/** @brief Initializes the SPI bus without binding any CS line yet. */
uint8_t spi_init(gpio_num_t mosi, gpio_num_t miso, gpio_num_t sclk);

/** @brief Adds a new SPI device with the selected CS pin and handle index. */
uint8_t addSpiDevice(gpio_num_t cs_pin, int index);

/** @brief Sends a single byte over SPI. */
uint8_t spi_write(uint8_t* data, int index);

/** @brief Sends three bytes (24 bits) over SPI. */
uint8_t spi_write24(uint8_t* data, int index);

/** @brief Performs a full-duplex SPI transfer. */
uint8_t spi_read(uint8_t* tx_data, uint8_t* rx_data, size_t length, int index);

/** @brief Sends an ADS1263 command byte such as START or RESET. */
uint8_t ads1263_sendCommand(uint8_t cmd, int index);

/** @brief Writes one ADS1263 register using the WREG command. */
uint8_t ads1263_writeReg(uint8_t reg, uint8_t data, int index);

/** @brief Reads one ADS1263 register using the RREG command frame. */
uint32_t ads1263_readReg(uint8_t reg, uint8_t index);

uint8_t spi_write16(uint8_t* data, int index);

uint8_t spi_deinit(void);

#endif // SPI_H
