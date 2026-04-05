# esp32-ads1263

Rozbudowany sterownik `ADS1263` dla ESP32 z obsługą rejestrów, komend i konfiguracji toru analogowego.

## Co zawiera
- funkcje odczytu i zapisu rejestrów
- komendy sterujące `START`, `STOP`, `RESET`
- konfigurację `MODE0`, `MODE1`, `MODE2`, `INPMUX`, `IDACMUX` i pozostałych rejestrów

## Zależności
- do repo jest dołączony prosty helper `spi.h` / `spi.c`
- opcjonalnie `esp32-uart-xor`

## Pliki
- `include/ads1263.h`
- `include/spi.h`
- `src/ads1263.c`
- `src/spi.c`

## Szybki start
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

Pełny przykład znajdziesz w `examples/basic_usage/basic_usage.c`.
