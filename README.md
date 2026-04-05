# esp32-ads1263

Advanced `ADS1263` driver for ESP32 with register access, command handling, and analog front-end configuration helpers.

## Features
- register read and write helpers
- control commands such as `START`, `STOP`, and `RESET`
- configuration for `MODE0`, `MODE1`, `MODE2`, `INPMUX`, `IDACMUX`, and related registers

## Dependencies
- the repository includes a simple `spi.h` / `spi.c` helper
- optional `esp32-uart-xor`

## Files
- `include/ads1263.h`
- `include/spi.h`
- `src/ads1263.c`
- `src/spi.c`

## Quick start
```c
#include "ads1263.h"
#include "spi.h"

void app_main(void)
{
    spi_init(GPIO_NUM_19, GPIO_NUM_21, GPIO_NUM_18);
    addSpiDevice(ADS1263_0_CS_PIN, ADS1263_INDEX_0);
    ads1263_softReset(ADS1263_INDEX_0);
    ads1263_setMode2Reg(ADS1263_INDEX_0, ADS1263_PGA_ENABLED, ADS1263_GAIN_1, ADS1263_DR_1200SPS);
}
```

See `examples/basic_usage/basic_usage.c` for a complete example.
