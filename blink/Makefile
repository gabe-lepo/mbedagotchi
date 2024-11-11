# Target
MCU = atmega328p

# Clock freq
F_CPU = 16000000UL # 16 MHz

# Optimization level
OPT = -Os

# Source, output files
SRC = blink.c
ELF = blink.elf
HEX = blink.hex
ASM = blink.lst

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

# ASM listing target
$(ASM): $(SRC)
	avr-gcc $(CFLAGS) -S -o $(ASM) $(SRC)

list: $(ASM)
	@echo "Assembly listing generated as $(ASM)"

# Upload target
upload: $(HEX)
	avrdude -v -patmega328p -carduino -P$(PORT) -b $(BAUD) -D -Uflash:w:$(HEX):i

# Clean target
clean:
	rm -f *.elf *.hex *.lst

# Dummy clean target
dummy:
	avr-gcc $(CFLAGS) -o dummy.elf dummy.c
	avr-objcopy -O ihex -R .eeprom dummy.elf dummy.hex
	avrdude -v -patmega328p -carduino -P$(PORT) -b $(BAUD) -D -Uflash:w:dummy.hex:i

# Phony target
.PHONY: build upload clean dummy list