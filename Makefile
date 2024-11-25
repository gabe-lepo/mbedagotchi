# Target
MCU = atmega328p

# Clock freq
F_CPU = 16000000UL # 16 MHz

# Optimization level
OPT = -Os

# Directories
DIR_LED = src/led
DIR_SPI = src/spi
DIR_UART = src/uart
DIR_MAIN = src/main
DIR_BUILD = build
DIR_SCREEN = src/ssd1681

# Source, output files
SRC = $(DIR_MAIN)/main.c $(DIR_SPI)/spi.c $(DIR_LED)/led.c $(DIR_UART)/uart.c $(DIR_SCREEN)/ssd1681.c
OBJ = $(DIR_BUILD)/main.o $(DIR_BUILD)/spi.o $(DIR_BUILD)/led.o $(DIR_BUILD)/uart.o $(DIR_SCREEN)/ssd1681.o
ELF = $(DIR_BUILD)/main.elf
HEX = $(DIR_BUILD)/main.hex

# AVRDUDE settings
PORT = /dev/cu.usbserial-AQ04QNJZ
BAUD = 115200

# Compiler/linker flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(OPT)
LDFLAGS = -mmcu=$(MCU)

# Default target
all: build upload

# Build target
build: $(HEX)

# Object file compilation
build/main.o: $(DIR_MAIN)/main.c
	mkdir -p build
	avr-gcc $(CFLAGS) -c $< -o $@

build/spi.o: $(DIR_SPI)/spi.c
	mkdir -p build
	avr-gcc $(CFLAGS) -c $< -o $@

build/led.o: $(DIR_LED)/led.c
	mkdir -p build
	avr-gcc $(CFLAGS) -c $< -o $@

build/uart.o: $(DIR_UART)/uart.c
	mkdir -p build
	avr-gcc $(CFLAGS) -c $< -o $@

build/uart.o: $(DIR_SCREEN)/ssd1681.c
	mkdir -p build
	avr-gcc $(CFLAGS) -c $< -o $@

# Link
$(ELF): $(OBJ)
	avr-gcc $(LDFLAGS) -o $(ELF) $(OBJ)

# Create HEX from ELF
$(HEX): $(ELF)
	avr-objcopy -O ihex -R .eeprom $(ELF) $(HEX)

# Upload target
upload: $(HEX)
	avrdude -v -patmega328p -carduino -P$(PORT) -b $(BAUD) -D -Uflash:w:$(HEX):i

# Clean target
clean:
	rm -rf build

# Phony target
.PHONY: all build upload clean