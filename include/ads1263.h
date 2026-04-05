#ifndef ADS1263_H
#define ADS1263_H


#define ADS1263_INDEX_0 0
#define ADS1263_0_CS_PIN     GPIO_NUM_5
#define ADS1263_0_DRDY_PIN   GPIO_NUM_21
#define ADS1263_0_RESET_PIN  GPIO_NUM_22

#define ADS1263_RREG 0x20
#define ADS1263_WREG 0x40


//komendy
#define ADS1263_NOP        0b00000000
#define ADS1263_RESET      0b00000110
#define ADS1263_START1     0b00001000
#define ADS1263_STOP1      0b00001010
#define ADS1263_START2     0b00001100
#define ADS1263_STOP2      0b00001110
#define ADS1263_RDATA1     0b00010010
#define ADS1263_RDATA2     0b00010100

//rejestry
#define ADS1263_POWER       0x01
#define ADS1263_INTERFACE   0x02
#define ADS1263_MODE0       0x03
#define ADS1263_MODE1       0x04
#define ADS1263_MODE2       0x05
#define ADS1263_INPMUX      0x06
#define ADS1263_OFCAL0      0x07
#define ADS1263_OFCAL1      0x08
#define ADS1263_OFCAL2      0x09
#define ADS1263_FSCAL0      0x0A
#define ADS1263_FSCAL1      0x0B
#define ADS1263_FSCAL2      0x0C
#define ADS1263_IDACMUX     0x0D
#define ADS1263_IDACMAG     0x0E
#define ADS1263_REFMUX      0x0F
#define ADS1263_TDACP       0x10
#define ADS1263_TDACN       0x11
#define ADS1263_GPIOCON     0x12
#define ADS1263_GPIODIR     0x13
#define ADS1263_GPIODAT     0x14
#define ADS1263_ADC2CFG     0x15
#define ADS1263_ADC2MUX     0x16
#define ADS1263_ADC2OFC0    0x17
#define ADS1263_ADC2OFC1    0x18
#define ADS1263_ADC2FSC0    0x19
#define ADS1263_ADC2FSC1    0x1A

// == POWER REGISTER ==
// Rejestr konfiguracji zasilania i źródeł odniesienia w ADC

// Bit RESET – (bit 4): sygnalizuje, czy nastąpił reset urządzenia (np. po soft/hard resecie)
// Wartość 1 oznacza, że wystąpił reset – można go wyczyścić, ustawiając 0
#define ADS1263_RESET_RST_BIT 0b0  // Ustawienie 0 – czyści flagę resetu

// == VBIAS – bias voltage enable (bit 1) ==
// Źródło napięcia odniesienia ~1/2 AVDD podłączone do AINCOM
// Przydatne, gdy nie masz stałej referencji odniesienia względem masy
#define ADS1263_DISABLE_VBIAS 0b0  // Wyłączone – AINCOM pozostaje niepodłączony
#define ADS1263_ENABLE_VBIAS  0b1  // Włączone – ~AVDD/2 trafia na AINCOM

// == INTREF – internal reference enable (bit 0) ==
// Wewnętrzne źródło odniesienia 2.5 V do użycia z REFPx/REFNx (np. REFP1/REFN1)
#define ADS1263_DISABLE_INTREF 0b0  // Korzystasz z zewnętrznego źródła referencyjnego
#define ADS1263_ENABLE_INTREF  0b1  // Włącz wewnętrzne 2.5 V VREF (np. jeśli nie masz zewnętrznego VREF)

// == INTERFACE REGISTER ==
//rejestr konfiguracji interfejsu, danych dodatkowych (timeout, bit statusu, sumy kontrolnej)

#define ADS1263_TIMEOUT_ENABLE 0b1 //timeout
#define ADS1263_TIMEOUT_DISABLE 0b0

#define ADS1263_STATUS_DISABLE 0b0 //bit statusu (np.: obsługa błędów)
#define ADS1263_STATUS_ENABLE 0b1

#define ADS1263_CRC_DISABLE 0b00 //suma kontrolna, patrz str.90 dokumentacji
#define ADS1263_CRC_MODE1 0b01
#define ADS1263_CRC_MODE2 0b10
#define ADS1263_CRC_MODE3 0b10
#define ADS1263_CRC_MODE4 0b11


// == MODE 0 REGISTER ==
//ustawienie 1 rejestru char. działania

#define ADS1263_REFREV_DISABLE 0b0 //obrócenie polaryzacji multipleksera referencyjnego wyłączone
#define ADS1263_REFREV_ENABLE 0b1

#define ADS1263_MODE_CONTINOUS 0b0 //tryb ciągły
#define ADS1263_MODE_SINGLE 0b1 //tryb one shot

#define ADS1263_CHOP_MODE_ALL_DISABLE 0b00
#define ADS1263_CHOP_MODE_INPUT_CHOP_ENABLE 0b01
#define ADS1263_CHOP_MODE_IDAC_ROTATION_ENABLED 0b10
#define ADS1263_CHOP_MODE_IDAC_ROTATION_AND_INPUT_CHOP_ENABLED 0b11

#define ADS1263_DELAY_0US     0b0000  // 0 µs (default)
#define ADS1263_DELAY_8_7US   0b0001  // 8.7 µs
#define ADS1263_DELAY_17US    0b0010  // 17 µs
#define ADS1263_DELAY_35US    0b0011  // 35 µs
#define ADS1263_DELAY_69US    0b0100  // 69 µs
#define ADS1263_DELAY_139US   0b0101  // 139 µs
#define ADS1263_DELAY_278US   0b0110  // 278 µs
#define ADS1263_DELAY_555US   0b0111  // 555 µs
#define ADS1263_DELAY_1_1MS   0b1000  // 1.1 ms
#define ADS1263_DELAY_2_2MS   0b1001  // 2.2 ms
#define ADS1263_DELAY_4_4MS   0b1010  // 4.4 ms
#define ADS1263_DELAY_8_8MS   0b1011  // 8.8 ms


// == MODE 1 REGISTER ==
// == FILTER[2:0] – Digital Filter Mode ==
#define ADS1263_FILTER_SINC1  0b000
#define ADS1263_FILTER_SINC2  0b001
#define ADS1263_FILTER_SINC3  0b010
#define ADS1263_FILTER_SINC4  0b011
#define ADS1263_FILTER_FIR    0b100  // Default


// == SBADC (bit 4) – Sensor Bias ADC Connection ==
#define ADS1263_SBADC_ADC1 0b0  // Default: Sensor bias connected to ADC1 mux out
#define ADS1263_SBADC_ADC2 0b1  // Sensor bias connected to ADC2 mux out

// == SBPOL (bit 3) – Sensor Bias Polarity ==
#define ADS1263_SBPOL_PULLUP   0b0  // Default: AINP pulled high, AINN pulled low
#define ADS1263_SBPOL_PULLDOWN 0b1  // AINP pulled low, AINN pulled high

// == SBMAG[2:0] – Sensor Bias Magnitude ==
#define ADS1263_SBMAG_NONE     0b000  // Default: No sensor bias
#define ADS1263_SBMAG_0_5UA    0b001
#define ADS1263_SBMAG_2UA      0b010
#define ADS1263_SBMAG_10UA     0b011
#define ADS1263_SBMAG_50UA     0b100
#define ADS1263_SBMAG_200UA    0b101
#define ADS1263_SBMAG_10M_OHM  0b110
#define ADS1263_SBMAG_RESERVED 0b111

// == MODE 2 REGISTER ==

#define ADS1263_PGA_ENABLED   0b0  // Default: PGA włączony
#define ADS1263_PGA_BYPASSED  0b1  // Ominięcie PGA

#define ADS1263_GAIN_1   0b000  // Default: 1 V/V
#define ADS1263_GAIN_2   0b001
#define ADS1263_GAIN_4   0b010
#define ADS1263_GAIN_8   0b011
#define ADS1263_GAIN_16  0b100
#define ADS1263_GAIN_32  0b101

#define ADS1263_DR_2_5SPS     0b0000
#define ADS1263_DR_5SPS       0b0001
#define ADS1263_DR_10SPS      0b0010
#define ADS1263_DR_16_6SPS    0b0011
#define ADS1263_DR_20SPS      0b0100  // Default
#define ADS1263_DR_50SPS      0b0101
#define ADS1263_DR_60SPS      0b0110
#define ADS1263_DR_100SPS     0b0111
#define ADS1263_DR_400SPS     0b1000
#define ADS1263_DR_1200SPS    0b1001
#define ADS1263_DR_2400SPS    0b1010
#define ADS1263_DR_4800SPS    0b1011
#define ADS1263_DR_7200SPS    0b1100
#define ADS1263_DR_14400SPS   0b1101
#define ADS1263_DR_19200SPS   0b1110
#define ADS1263_DR_38400SPS   0b1111

// == INPMUX REGISTER ==

// Mux P - wejście dodatnie
#define ADS1263_MUXP_AIN0        0b0000
#define ADS1263_MUXP_AIN1        0b0001
#define ADS1263_MUXP_AIN2        0b0010
#define ADS1263_MUXP_AIN3        0b0011
#define ADS1263_MUXP_AIN4        0b0100
#define ADS1263_MUXP_AIN5        0b0101
#define ADS1263_MUXP_AIN6        0b0110
#define ADS1263_MUXP_AIN7        0b0111
#define ADS1263_MUXP_AIN8        0b1000
#define ADS1263_MUXP_AIN9        0b1001
#define ADS1263_MUXP_AINCOM      0b1010
#define ADS1263_MUXP_TEMP        0b1011  // Temperaturowy czujnik (plus)
#define ADS1263_MUXP_AVDD        0b1100  // Analog power supply monitor +
#define ADS1263_MUXP_DVDD        0b1101  // Digital power supply monitor +
#define ADS1263_MUXP_TDAC_POS    0b1110  // TDAC test signal +
#define ADS1263_MUXP_FLOAT       0b1111  // Open (brak połączenia)

// Mux N - wejście negatywne 

#define ADS1263_MUXN_AIN0        0b0000
#define ADS1263_MUXN_AIN1        0b0001
#define ADS1263_MUXN_AIN2        0b0010
#define ADS1263_MUXN_AIN3        0b0011
#define ADS1263_MUXN_AIN4        0b0100
#define ADS1263_MUXN_AIN5        0b0101
#define ADS1263_MUXN_AIN6        0b0110
#define ADS1263_MUXN_AIN7        0b0111
#define ADS1263_MUXN_AIN8        0b1000
#define ADS1263_MUXN_AIN9        0b1001
#define ADS1263_MUXN_AINCOM      0b1010
#define ADS1263_MUXN_TEMP        0b1011  // Temperaturowy czujnik (minus)
#define ADS1263_MUXN_AVDD        0b1100  // Analog power supply monitor -
#define ADS1263_MUXN_DVDD        0b1101  // Digital power supply monitor -
#define ADS1263_MUXN_TDAC_NEG    0b1110  // TDAC test signal -
#define ADS1263_MUXN_FLOAT       0b1111  // Open (brak połączenia)


// == IDACMUX REGISTER ==
// IDAC1 Output Multiplexer (MUX1[3:0])
#define ADS1263_IDAC1_AIN0         0b0000
#define ADS1263_IDAC1_AIN1         0b0001
#define ADS1263_IDAC1_AIN2         0b0010
#define ADS1263_IDAC1_AIN3         0b0011
#define ADS1263_IDAC1_AIN4         0b0100
#define ADS1263_IDAC1_AIN5         0b0101
#define ADS1263_IDAC1_AIN6         0b0110
#define ADS1263_IDAC1_AIN7         0b0111
#define ADS1263_IDAC1_AIN8         0b1000
#define ADS1263_IDAC1_AIN9         0b1001
#define ADS1263_IDAC1_AINCOM       0b1010
#define ADS1263_IDAC1_NC           0b1011  // No connection (default)


// IDAC2 Output Multiplexer (MUX2[3:0])
#define ADS1263_IDAC2_AIN0         0b0000
#define ADS1263_IDAC2_AIN1         0b0001
#define ADS1263_IDAC2_AIN2         0b0010
#define ADS1263_IDAC2_AIN3         0b0011
#define ADS1263_IDAC2_AIN4         0b0100
#define ADS1263_IDAC2_AIN5         0b0101
#define ADS1263_IDAC2_AIN6         0b0110
#define ADS1263_IDAC2_AIN7         0b0111
#define ADS1263_IDAC2_AIN8         0b1000
#define ADS1263_IDAC2_AIN9         0b1001
#define ADS1263_IDAC2_AINCOM       0b1010
#define ADS1263_IDAC2_NC           0b1011  // No connection (default)

// == IDACMAG REGISTER ==
// IDAC1 Current Magnitude (bits 3:0)
#define ADS1263_IDAC1_OFF       0b0000  // 0 µA (default)
#define ADS1263_IDAC1_50uA      0b0001
#define ADS1263_IDAC1_100uA     0b0010
#define ADS1263_IDAC1_250uA     0b0011
#define ADS1263_IDAC1_500uA     0b0100
#define ADS1263_IDAC1_750uA     0b0101
#define ADS1263_IDAC1_1000uA    0b0110
#define ADS1263_IDAC1_1500uA    0b0111
#define ADS1263_IDAC1_2000uA    0b1000
#define ADS1263_IDAC1_2500uA    0b1001
#define ADS1263_IDAC1_3000uA    0b1010

// IDAC2 Current Magnitude (bits 7:4)
#define ADS1263_IDAC2_OFF       0b0000  // 0 µA (default)
#define ADS1263_IDAC2_50uA      0b0001
#define ADS1263_IDAC2_100uA     0b0010
#define ADS1263_IDAC2_250uA     0b0011
#define ADS1263_IDAC2_500uA     0b0100
#define ADS1263_IDAC2_750uA     0b0101
#define ADS1263_IDAC2_1000uA    0b0110
#define ADS1263_IDAC2_1500uA    0b0111
#define ADS1263_IDAC2_2000uA    0b1000
#define ADS1263_IDAC2_2500uA    0b1001
#define ADS1263_IDAC2_3000uA    0b1010


// REF Positive MUX (RMUXP[2:0])
#define ADS1263_REF_MUXP_INTREF       0b000  // Internal 2.5 V reference – P (default)
#define ADS1263_REF_MUXP_AIN0         0b001  // External AIN0
#define ADS1263_REF_MUXP_AIN2         0b010  // External AIN2
#define ADS1263_REF_MUXP_AIN4         0b011  // External AIN4
#define ADS1263_REF_MUXP_AVDD         0b100  // Internal analog supply (AVDD)

// REF Negative MUX (RMUXN[2:0])
#define ADS1263_REF_MUXN_INTREF       0b000  // Internal 2.5 V reference – N (default)
#define ADS1263_REF_MUXN_AIN1         0b001  // External AIN1
#define ADS1263_REF_MUXN_AIN3         0b010  // External AIN3
#define ADS1263_REF_MUXN_AIN5         0b011  // External AIN5
#define ADS1263_REF_MUXN_AVSS         0b100  // Internal analog supply (AVSS)

// TDACP Output Connection
#define ADS1263_TDACP_DISCONNECTED   0b0
#define ADS1263_TDACP_CONNECTED_AIN6 0b1

// TDACP Magnitude (V w odniesieniu do V_AVSS)
#define ADS1263_TDACP_4_5V    0b01001
#define ADS1263_TDACP_3_5V    0b01000
#define ADS1263_TDACP_3_0V    0b00111
#define ADS1263_TDACP_2_75V   0b00110
#define ADS1263_TDACP_2_625V  0b00101
#define ADS1263_TDACP_2_53125V 0b00100
#define ADS1263_TDACP_2_515625V 0b00011
#define ADS1263_TDACP_2_5078125V 0b00010
#define ADS1263_TDACP_2_5V    0b00001
#define ADS1263_TDACP_2_4984375V 0b10001
#define ADS1263_TDACP_2_484375V 0b10010
#define ADS1263_TDACP_2_46875V  0b10011
#define ADS1263_TDACP_2_4375V   0b10100
#define ADS1263_TDACP_2_375V    0b10101
#define ADS1263_TDACP_2_25V     0b10110
#define ADS1263_TDACP_2_0V      0b10111
#define ADS1263_TDACP_1_5V      0b11000
#define ADS1263_TDACP_0_5V      0b11001

// TDACN Output Connection
#define ADS1263_TDACN_DISCONNECTED   0b0
#define ADS1263_TDACN_CONNECTED_AIN7 0b1

// TDACN Magnitude 
#define ADS1263_TDACN_4_5V    0b01001
#define ADS1263_TDACN_3_5V    0b01000
#define ADS1263_TDACN_3_0V    0b00111
#define ADS1263_TDACN_2_75V   0b00110
#define ADS1263_TDACN_2_625V  0b00101
#define ADS1263_TDACN_2_53125V 0b00100
#define ADS1263_TDACN_2_515625V 0b00011
#define ADS1263_TDACN_2_5078125V 0b00010
#define ADS1263_TDACN_2_5V    0b00001
#define ADS1263_TDACN_2_4984375V 0b10001
#define ADS1263_TDACN_2_484375V 0b10010
#define ADS1263_TDACN_2_46875V  0b10011
#define ADS1263_TDACN_2_4375V   0b10100
#define ADS1263_TDACN_2_375V    0b10101
#define ADS1263_TDACN_2_25V     0b10110
#define ADS1263_TDACN_2_0V      0b10111
#define ADS1263_TDACN_1_5V      0b11000
#define ADS1263_TDACN_0_5V      0b11001

//GPIOCON register
#define ADS1263_PIN_NOCONNECTED 0
#define ADS1263_PIN_CONNECTED 1

//GPIODIR register
#define ADS1263_PIN_OUTPUT 0
#define ADS1263_PIN_INPUT 1


//GPIODAT register
#define ADS1263_PIN_LOW 0
#define ADS1263_PIN_HIGH 1




volatile bool drdy_flag = false;

static void IRAM_ATTR drdy_isr_handler(void* arg);

bool ads1263_data_ready();

// Wysyła komendę do ADS1263 (np. START, RESET)
uint8_t ads1263_sendCommand(uint8_t cmd, int index);

// Zapisuje do rejestru ADS1263 (WREG)
uint8_t ads1263_writeReg(uint8_t reg, uint8_t data, int index);

// Czyta 3 bajty z rejestru (RREG + 2 dummy bajty)
uint32_t ads1263_readReg(uint8_t reg, uint8_t index);


void ads1263_reset(gpio_num_t RESET_PIN);

uint8_t ads1263_noOperation(int index);
uint8_t ads1263_softReset(int index) ;
uint8_t ads1263_start1(int index);
uint8_t ads1263_stop1(int index);
uint8_t ads1263_start2(int index); 
uint8_t ads1263_stop2(int index) ;
uint8_t ads1263_setPowerReg(int index, uint8_t reset, uint8_t vbias, uint8_t intref);
uint32_t ads1263_readPowerReg(int index);
uint8_t ads1263_setInterfaceReg(int index, uint8_t timeout, uint8_t status, uint8_t crc);
uint32_t ads1263_readInterfaceReg(int index)
uint8_t ads1263_setMode0Reg(int index, uint8_t refrev, uint8_t runmode, uint8_t chop, uint8_t delay);
uint32_t ads1263_readMode0Reg(int index);
uint8_t ads1263_setMode1Reg(int index, uint8_t filter, uint8_t sbadc, uint8_t sbpol, uint8_t sbmag);
uint32_t ads1263_readMode1Reg(int index) ;
uint8_t ads1263_setMode2Reg(int index, uint8_t bypass, uint8_t gain, uint8_t datarate);
uint32_t ads1263_readMode2Reg(int index);
uint8_t ads1263_setInputMuxReg(int index, uint8_t muxp, uint8_t muxn) ;
uint32_t ads1263_readInputMuxReg(int index) ;
uint8_t ads1263_setIdacMuxReg(int index, uint8_t mux2, uint8_t mux1) ;
uint32_t ads1263_readIdacMuxReg(int index) ;
uint8_t ads1263_setIdacMagReg(int index, uint8_t mag2, uint8_t mag1);
uint32_t ads1263_readIdacMagReg(int index);
uint8_t ads1263_setRefMuxReg(int index, uint8_t rMuxP2, uint8_t rMuxP1);
uint32_t ads1263_readRefMuxReg(int index);
uint8_t ads1263_setTdaCpReg(int index, uint8_t outP, uint8_t magP);
uint32_t ads1263_readTdaCpReg(int index);
uint8_t ads1263_setTdaCpnReg(int index, uint8_t outN, uint8_t magN);
uint32_t ads1263_readTdaCnReg(int index);
uint8_t ads1263_setGPIOCONReg(int index, int gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3, uint8_t gpio4, uint8_t gpio5, uint8_t gpio6,uint8_t gpio7);
uint32_t ads1263_readGPIOCONReg(int index);
uint8_t ads1263_setGPIODIRReg(int index, int gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3, uint8_t gpio4, uint8_t gpio5, uint8_t gpio6,uint8_t gpio7);
uint32_t ads1263_readGPIODIRReg(int index);
uint8_t ads1263_setGPIODATReg(int index, int gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3, uint8_t gpio4, uint8_t gpio5, uint8_t gpio6,uint8_t gpio7);
uint32_t ads1263_readGPIODATReg(int index);
int32_t ads1263_voltage_to_bin(double voltage_offset, double vref); 
uint8_t ads1263_setOffsetReg(int index, double voltage_offset, double vref);
uint8_t ads1263_setFullscaleReg(int index, double fullscale_voltage, double vref);
uint32_t ads1263_readData(int index);
uint8_t ads1263_init(int index, uint8_t cs_pin, uint8_t RESET_PIN, uint8_t DRDY_PIN);
