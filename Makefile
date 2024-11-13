# Target
MCU = atmega328p

# Clock freq
F_CPU = 16000000UL # 16 MHz

# Optimization level
OPT = -Os

# Source, output files
SRC = blink/blink.c sleep/sleep.c
ELF = build/blink.elf
HEX = build/blink.hex

# AVRDUDE settings
PORT = /dev/cu.usbserial-AQ04QNJZ
BAUD = 115200

# Compiler/linker flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(OPT)
LDFLAGS = -mmcu=$(MCU)

# Default target
all: clean build upload

# Build target
build: $(HEX)
$(ELF): $(SRC)
	avr-gcc $(CFLAGS) -o $(ELF) $(SRC)

$(HEX): $(ELF)
	avr-objcopy -O ihex -R .eeprom $(ELF) $(HEX)

# Upload target
upload: $(HEX)
	avrdude -v -patmega328p -carduino -P$(PORT) -b $(BAUD) -D -Uflash:w:$(HEX):i

# Clean target
clean:
	rm -rf build/*.elf build/*.hex
	mkdir -p build

# Phony target
.PHONY: all build upload clean