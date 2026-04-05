/**
 * @file ads1263.c
 * @brief ADS1263 driver implementation.
 */

#include "ads1263.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "spi.h"
#include "uart.h"  
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "uart.h"
#include "spi.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief DRDY interrupt handler.
 *
 * @param arg Unused ISR argument
 */
static void IRAM_ATTR drdy_isr_handler(void* arg) {
    drdy_flag = true;
}

/**
 * @brief Returns true when the DRDY interrupt has fired.
 */
bool ads1263_data_ready() {
    if (drdy_flag) {
        drdy_flag = false;
        return true;
    }
    return false;
}

uint32_t ads1263_readReg(uint8_t reg, uint8_t index) {
    uint8_t tx[3] = { ADS1263_RREG | reg , 0x00, 0xFF };
    uint8_t rx[3] = { 0 };

    if (spi_read(tx, rx, 3, index) != 0x00)
        return 0xFFFFFFFF;

    uint32_t value = ((uint32_t)rx[0] << 16) | ((uint32_t)rx[1] << 8) | rx[2];
    return value;
}

uint8_t ads1263_writeReg(uint8_t reg, uint8_t data, int index) {
    uint8_t cmd[3];
    cmd[0] = ADS1263_WREG | reg;  // WREG command with register address
    cmd[1] = 0x00;                // One data byte follows
    cmd[2] = data;

    return spi_write24(cmd, index);
}


uint8_t ads1263_sendCommand(uint8_t cmd, int index) {
    return spi_write(&cmd, index);  // Pass the command byte by address
}

void ads1263_reset(gpio_num_t RESET_PIN) {
    gpio_set_level(RESET_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(100));
    gpio_set_level(RESET_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
    gpio_set_level(RESET_PIN, 1);
}


uint8_t ads1263_noOperation(int index) {
    return ads1263_sendCommand(ADS1263_NOP, index);
}

uint8_t ads1263_softReset(int index) {
    return ads1263_sendCommand(ADS1263_RESET, index);
}

uint8_t ads1263_start1(int index) {
    return ads1263_sendCommand(ADS1263_START1, index);
}

uint8_t ads1263_stop1(int index) {
    return ads1263_sendCommand(ADS1263_STOP1, index);
}

uint8_t ads1263_start2(int index) {
    return ads1263_sendCommand(ADS1263_START2, index);
}

uint8_t ads1263_stop2(int index) {
    return ads1263_sendCommand(ADS1263_STOP2, index);
}

uint8_t ads1263_setPowerReg(int index, uint8_t reset, uint8_t vbias, uint8_t intref){
     uint8_t data = (reset << 4) | (vbias << 1) | intref;
    return ads1263_writeReg(ADS1263_POWER, data, index);
}

uint32_t ads1263_readPowerReg(int index){
    return ads1263_readReg(ADS1263_POWER, index);
}

uint8_t ads1263_setInterfaceReg(int index, uint8_t timeout, uint8_t status, uint8_t crc){
     uint8_t data = (timeout << 3 | (status << 2) | crc);
    return ads1263_writeReg(ADS1263_INTERFACE, data, index);
}

uint32_t ads1263_readInterfaceReg(int index){
    return ads1263_readReg(ADS1263_INTERFACE, index);
}

uint8_t ads1263_setMode0Reg(int index, uint8_t refrev, uint8_t runmode, uint8_t chop, uint8_t delay){
     uint8_t data = (refrev << 7 | (runmode << 6) | (chop << 4) | delay);
    return ads1263_writeReg(ADS1263_MODE0, data, index);
}

uint32_t ads1263_readMode0Reg(int index){
    return ads1263_readReg(ADS1263_MODE0, index);
}

uint8_t ads1263_setMode1Reg(int index, uint8_t filter, uint8_t sbadc, uint8_t sbpol, uint8_t sbmag) {
    uint8_t data = (filter << 5) | (sbadc << 4) | (sbpol << 3) | sbmag;
    return ads1263_writeReg(ADS1263_MODE1, data, index);
}

uint32_t ads1263_readMode1Reg(int index) {
    return ads1263_readReg(ADS1263_MODE1, index);
}

uint8_t ads1263_setMode2Reg(int index, uint8_t bypass, uint8_t gain, uint8_t datarate) {
    uint8_t data = (bypass << 7) | (gain << 4) | (datarate & 0x0F);
    return ads1263_writeReg(ADS1263_MODE2, data, index);
}

uint32_t ads1263_readMode2Reg(int index) {
    return ads1263_readReg(ADS1263_MODE2, index);
}
// Register reconfiguration helpers
uint8_t ads1263_setInputMuxReg(int index, uint8_t muxp, uint8_t muxn) {
    uint8_t reg_value = (muxp << 4) | muxn;
    return ads1263_writeReg(ADS1263_INPMUX, reg_value, index);
}

uint32_t ads1263_readInputMuxReg(int index) {
    return ads1263_readReg(ADS1263_INPMUX, index);
}

uint8_t ads1263_setIdacMuxReg(int index, uint8_t mux2, uint8_t mux1) {
    uint8_t reg_value = (mux2 << 4) | mux1;
    return ads1263_writeReg(ADS1263_IDACMUX, reg_value, index);
}

uint32_t ads1263_readIdacMuxReg(int index) {
    return ads1263_readReg(ADS1263_IDACMUX, index);
}

uint8_t ads1263_setIdacMagReg(int index, uint8_t mag2, uint8_t mag1) {
    uint8_t reg_value = (mag2 << 4) | mag1;
    return ads1263_writeReg(ADS1263_IDACMAG, reg_value, index);
}

uint32_t ads1263_readIdacMagReg(int index) {
    return ads1263_readReg(ADS1263_IDACMAG, index);
}

uint8_t ads1263_setRefMuxReg(int index, uint8_t rMuxP2, uint8_t rMuxP1) {
    uint8_t reg_value = (rMuxP2 << 3) | rMuxP1;
    return ads1263_writeReg(ADS1263_REFMUX, reg_value, index);
}

uint32_t ads1263_readRefMuxReg(int index) {
    return ads1263_readReg(ADS1263_REFMUX, index);
}

uint8_t ads1263_setTdaCpReg(int index, uint8_t outP, uint8_t magP) {
    uint8_t reg_value = (outP << 7) | magP;
    return ads1263_writeReg(ADS1263_TDACP, reg_value, index);
}

uint32_t ads1263_readTdaCpReg(int index) {
    return ads1263_readReg(ADS1263_TDACP, index);
}

uint8_t ads1263_setTdaCpnReg(int index, uint8_t outN, uint8_t magN) {
    uint8_t reg_value = (outN << 7) | magN;
    return ads1263_writeReg(ADS1263_TDACN, reg_value, index);
}

uint32_t ads1263_readTdaCnReg(int index) {
    return ads1263_readReg(ADS1263_TDACN, index);
}

uint8_t ads1263_setGPIOCONReg(int index, int gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3, uint8_t gpio4, uint8_t gpio5, uint8_t gpio6,uint8_t gpio7) {
    uint8_t reg_value = (gpio0 << 7) | (gpio1 << 6) | (gpio2 << 5) | (gpio3 << 4) | (gpio4 << 3) | (gpio5 << 2) | (gpio6 << 1) | gpio7;
    return ads1263_writeReg(ADS1263_GPIOCON, reg_value, index);
}

uint32_t ads1263_readGPIOCONReg(int index) {
    return ads1263_readReg(ADS1263_GPIOCON, index);
}

uint8_t ads1263_setGPIODIRReg(int index, int gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3, uint8_t gpio4, uint8_t gpio5, uint8_t gpio6,uint8_t gpio7) {
    uint8_t reg_value = (gpio0 << 7) | (gpio1 << 6) | (gpio2 << 5) | (gpio3 << 4) | (gpio4 << 3) | (gpio5 << 2) | (gpio6 << 1) | gpio7;
    return ads1263_writeReg(ADS1263_GPIODIR, reg_value, index);
}

uint32_t ads1263_readGPIODIRReg(int index) {
    return ads1263_readReg(ADS1263_GPIODIR, index);
}

uint8_t ads1263_setGPIODATReg(int index, int gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3, uint8_t gpio4, uint8_t gpio5, uint8_t gpio6,uint8_t gpio7) {
    uint8_t reg_value = (gpio0 << 7) | (gpio1 << 6) | (gpio2 << 5) | (gpio3 << 4) | (gpio4 << 3) | (gpio5 << 2) | (gpio6 << 1) | gpio7;
    return ads1263_writeReg(ADS1263_GPIODAT, reg_value, index);
}

uint32_t ads1263_readGPIODATReg(int index) {
    return ads1263_readReg(ADS1263_GPIODAT, index);
}

int32_t ads1263_voltage_to_bin(double voltage_offset, double vref) {
    // Convert the offset into a signed 24-bit value (two's complement).
    // Range: ±(2^23 - 1)
    double scale = (double)(1 << 23);  // 2^23 = 8,388,608
    double raw = (voltage_offset / vref) * scale;

    // Round and clamp to the signed 24-bit range.
    if (raw > 8388607.0)
        raw = 8388607.0;
    else if (raw < -8388608.0)
        raw = -8388608.0;

    return (int32_t)(raw);
}


uint8_t ads1263_setOffsetReg(int index, double voltage_offset, double vref) {
    int32_t bin = ads1263_voltage_to_bin(voltage_offset, vref);

    uint8_t byte0 = (bin >> 16) & 0xFF;  // MSB
    uint8_t byte1 = (bin >> 8) & 0xFF;
    uint8_t byte2 = bin & 0xFF;          // LSB

    if (ads1263_writeReg(ADS1263_OFCAL0, byte0, index) == 0xFF) return 0xFF;
    if (ads1263_writeReg(ADS1263_OFCAL1, byte1, index) == 0xFF) return 0xFF;
    if (ads1263_writeReg(ADS1263_OFCAL2, byte2, index) == 0xFF) return 0xFF;

    return 0x00;
}

uint8_t ads1263_setFullscaleReg(int index, double fullscale_voltage, double vref) {
    int32_t bin = ads1263_voltage_to_bin(fullscale_voltage, vref);  // Same conversion as offset

    uint8_t byte0 = (bin >> 16) & 0xFF;  // MSB
    uint8_t byte1 = (bin >> 8) & 0xFF;
    uint8_t byte2 = bin & 0xFF;         // LSB

    if (ads1263_writeReg(ADS1263_FSCAL0, byte0, index) == 0xFF) return 0xFF;
    if (ads1263_writeReg(ADS1263_FSCAL1, byte1, index) == 0xFF) return 0xFF;
    if (ads1263_writeReg(ADS1263_FSCAL2, byte2, index) == 0xFF) return 0xFF;

    return 0x00;
}

// This helper reads the 32-bit data frame returned by RDATA1.
uint32_t ads1263_readData(int index) {
    uint8_t tx_buf[5] = { ADS1263_RDATA1, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t rx_buf[5] = { 0 };

    if (spi_read(tx_buf, rx_buf, 5, index) != 0x00)
        return 0xFFFFFFFF;

    // Skip the first byte (status) and use the next four bytes as data.
    uint32_t value = ((uint32_t)rx_buf[1] << 24) |
                     ((uint32_t)rx_buf[2] << 16) |
                     ((uint32_t)rx_buf[3] << 8)  |
                     (rx_buf[4]);

    return value;
}


uint8_t ads1263_init(int index, uint8_t cs_pin, uint8_t RESET_PIN, uint8_t DRDY_PIN){

if (addSpiDevice(cs_pin, index) == 0xFF){
    return 0xff;
}
    gpio_set_direction(RESET_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(DRDY_PIN, GPIO_MODE_INPUT);

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << DRDY_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(DRDY_PIN, drdy_isr_handler, NULL);

    ads1263_reset(RESET_PIN);
    vTaskDelay(pdMS_TO_TICKS(100));
    
// 1. Power and reference configuration
ads1263_setPowerReg(index, ADS1263_RESET_RST_BIT, ADS1263_DISABLE_VBIAS, ADS1263_DISABLE_INTREF); // External VREF

// 2. Interface configuration
ads1263_setInterfaceReg(index, ADS1263_TIMEOUT_DISABLE, ADS1263_STATUS_DISABLE, ADS1263_CRC_DISABLE);

// 3. Operating mode: continuous conversion, no chop, no startup delay
ads1263_setMode0Reg(index, ADS1263_REFREV_DISABLE, ADS1263_MODE_CONTINOUS, ADS1263_CHOP_MODE_ALL_DISABLE, ADS1263_DELAY_0US);

// 4. Filter setup: SINC1 for the highest readout speed, no sensor bias
ads1263_setMode1Reg(index, ADS1263_FILTER_SINC1, ADS1263_SBADC_ADC1, ADS1263_SBPOL_PULLDOWN, ADS1263_SBMAG_NONE);

// 5. Disable the PGA for a 0-3.3 V full-scale input and select the data rate
ads1263_setMode2Reg(index, ADS1263_PGA_BYPASSED, ADS1263_GAIN_1, ADS1263_DR_38400SPS);

// 6. Input mux: differential input AIN0 - AIN1
ads1263_setInputMuxReg(index, ADS1263_MUXP_AIN0, ADS1263_MUXN_AIN1);

// 7. Reference mux
ads1263_setRefMuxReg(index, ADS1263_REF_MUXP_AVDD, ADS1263_REF_MUXN_AVSS); // Adjust to your actual REFPx/REFNx wiring



return 0;
}
