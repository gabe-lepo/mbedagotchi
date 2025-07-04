# mbedagotchi

Tamagotchi-like embedded device. As bare metal as possible.

## Toolchain setup

To setup avr-gcc:

1. `brew tap osx-cross/avr`
2. `brew install avr-gcc`

To setup avrdude:

1. `brew install avrdude`

Check program size and memory usage:

`avr-size build/main.elf`

## Makefile

Make note of the `$(PORT)` definition, this is the USB port the MCU is plugged into. So this value will need to change depending on where it's plugged in. Use the Arudio IDE to identify the `/dev` path

## Documentation

I have included in `docs/` the following:

- ATMega328P datasheet
- AVR architecture instruction set manual
- Pinout of the Arduino Nano clone board im using for prototyping
- Fritzing project file (very early WIP)

## SPI, SSD1681, SSD1306 Info

### Notes

Links:

- [EInk Display Product Page](https://www.microcenter.com/product/632695/inland-154-inch-e-ink-lcd-display-screen)
- [OLED Display Product Page](https://www.adafruit.com/product/938)

Datasheet notes:

- PRSPI bit may need to 0 to enable SPI, but this may only be for USART>SPI
  control...
- SPI master inits comm cycle when slave-select pin is pulled low
  - Then master/slave prepare packet data in shift registers
  - Master generates required SCK signal
- After each data packet, master syncs slave by pulling SS high
- No automatic control of SS when master
- Writing byte to SPI DR starts SCK generator, then 8 bits shifted to slave
  - After shifting 1 byte, SCK generator stops and sets EOT flag in SPIF
- Request interrupt by setting SPIE bit in SPCR
- Continue to shift more bytes, or if done, signal end of packet with SS high
  - Last byte is kept in buffer register for later
- Single buffer for transmit as master, must wait for shift cycle to complete
  before next byte in SPDR

## Pinouts

### ATMega328p to SSD1681 E-Ink Screen

| Board Function | Board Pin | AVR Pin | Direction | Screen Function      | Notes                                                         |
| -------------- | --------- | ------- | --------- | -------------------- | ------------------------------------------------------------- |
| SS             | D10       | PB2     | →         | CS (chip select)     |                                                               |
| MOSI           | D11       | PB3     | →         | SDI (serial data in) | This screen only has serial in, no ability to output SPI data |
| SCK            | D13       | PB5     | →         | CLK (clock)          |                                                               |
| OC1A           | D9        | PB1     | →         | D/C (data/command)   |                                                               |
| CLK/CP1        | D8        | PB0     | →         | RES (reset)          |                                                               |
| GPIO           | D2        | PD2     | ←         | BUSY (busy status)   |                                                               |

### ATMega328p to SSD1306 OLED Screen

| Board Function | Board Pin | AVR Pin | Direction | Screen Function | Notes                                                |
| -------------- | --------- | ------- | --------- | --------------- | ---------------------------------------------------- |
| SS             | D10       | PB2     | →         | CS              |                                                      |
| MOSI           | D11       | PB3     | →         | Data            | Only input to screen, ssd1306 has no data outs       |
| SCK            | D13       | PB5     | →         | CLK             |                                                      |
| OC1A           | D9        | PB1     | →         | A0 / DC         |                                                      |
| CLK/CP1        | D8        | PB0     | →         | RST             |                                                      |
|                |           |         | ←         | 3Vo             | Screen provides 3V output, THIS IS NOT A BUSY SIGNAL |

### Other

| Board Function | Arduino Pin | AVR Pin | Direction | Device Function | Notes                                                                            |
| -------------- | ----------- | ------- | --------- | --------------- | -------------------------------------------------------------------------------- |
| GPIO           | D12         | PB4     | →         | Breadboard LED  | The Arduino clone board has a built-in LED, but this is blocked during SPI comms |
