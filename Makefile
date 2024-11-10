# Target
MCU = atmega328p

# Clock freq
F_CPU = 16000000UL # 16 MHz

# Optimization level
OPT = -Os

# Source, output files
SRC = dummy.c
ELF = dummy.elf
HEX = dummy.hex

# AVRDUDE settings
PORT = /dev/cu.usbserial-AQ04QNJZ # Right most USB3.1 port on my hub
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
	rm -f $(ELF) $(HEX)

cleanall:
	rm -f *.elf *.hex

# Phony target
.PHONY: build upload clean cleanall