# mbedagotchi

Tamagotchi-like embedded device. As bare metal as possible.

## Toolchain setup

To setup avr-gcc:

1. `brew tap osx-cross/avr`
2. `brew install avr-gcc`

To setup avrdude:

1. `brew install avrdude`

## Makefile

Make note of the `$(PORT)` definition, this is the USB port the MCU is plugged into. So this value will need to change depending on where it's plugged in. Use the Arudio IDE to identify the `/dev` path

## Documentation

I have included in `docs/` the following:

- ATMega328P datasheet
- AVR architecture instruction set manual
- Pinout of the Arduino Nano clone board im using for prototyping
- Fritzing project file (very early WIP)

Other than the `.fzz`, I do not own nor did I create anything in that directory. Please don't sue me :)
