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
