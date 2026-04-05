#include "ads1263.h"
#include "spi.h"

void app_main(void)
{
    spi_init(GPIO_NUM_19, GPIO_NUM_21, GPIO_NUM_18);
    addSpiDevice(ADS1263_0_CS_PIN, ADS1263_INDEX_0);
    ads1263_softReset(ADS1263_INDEX_0);
    ads1263_setMode2Reg(ADS1263_INDEX_0, ADS1263_PGA_ENABLED, ADS1263_GAIN_1, ADS1263_DR_1200SPS);
}
