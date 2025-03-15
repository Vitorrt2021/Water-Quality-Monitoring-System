CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = 

# Simulation targets
SIM_SRC = water_quality_monitor.c
SIM_OBJ = $(SIM_SRC:.c=.o)
SIM_TARGET = water_quality_monitor

# AVR targets (for reference, requires avr-gcc)
MCU = atmega328p
F_CPU = 16000000UL
AVR_SRC = water_quality_monitor_embedded.c
AVR_TARGET = water_quality_monitor_embedded.hex
AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PORT = /dev/ttyUSB0

# Default target
all: $(SIM_TARGET)

# Simulation build
$(SIM_TARGET): $(SIM_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# AVR build (for reference)
avr: $(AVR_TARGET)

$(AVR_TARGET): $(AVR_SRC)
	avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Os -o $(AVR_TARGET:.hex=.elf) $^
	avr-objcopy -O ihex -R .eeprom $(AVR_TARGET:.hex=.elf) $@

# Upload to AVR (for reference)
upload: $(AVR_TARGET)
	avrdude -p $(MCU) -c $(AVRDUDE_PROGRAMMER) -P $(AVRDUDE_PORT) -U flash:w:$<

# Clean up
clean:
	rm -f $(SIM_TARGET) $(SIM_OBJ) $(AVR_TARGET) $(AVR_TARGET:.hex=.elf)

.PHONY: all clean avr upload