#include "ssd1681.h"
#include "../spi/spi.h"
#include "../uart/uart.h"
#include "avr/io.h"
#include <stdint.h>
#include <util/delay.h>

void screen_init(void) {
  print_string("# Initializing SSD1681...");

  // Reset first
  spi_reset();

  // Wait for display to be ready after reset
  _delay_ms(10);
  spi_wait_for_idle();
  print_string("# Post-reset wait complete");

  // Driver output control - to orient display
  spi_send_command(DRIVER_OUTPUT_CONTROL);
  spi_send_data((DISPLAY_HEIGHT - 1) & 0xFF);        // MUX setting low
  spi_send_data(((DISPLAY_HEIGHT - 1) >> 8) & 0xFF); // MUX setting high
  spi_send_data(0x00);                               // GD = 0, SM = 0, TB = 0
  _delay_ms(10);

  // Booster soft start - power supply
  spi_send_command(BOOSTER_SOFT_START_CONTROL);
  spi_send_data(0xD7);
  spi_send_data(0xD6);
  spi_send_data(0x9D);
  _delay_ms(10);

  // VCOM setting - for contrast
  spi_send_command(WRITE_VCOM_REGISTER);
  spi_send_data(0xA8);
  _delay_ms(10);

  // Dummy line period
  spi_send_command(SET_DUMMY_LINE_PERIOD);
  spi_send_data(0x1A);
  _delay_ms(10);

  // Gate time
  spi_send_command(SET_GATE_TIME);
  spi_send_data(0x08);
  _delay_ms(10);

  // Data entry mode - controls how data is written
  spi_send_command(DATA_ENTRY_MODE_SETTING);
  spi_send_data(0x03);
  _delay_ms(10);

  // Wait for init to complete
  _delay_ms(100);
  print_string("# SSD1681 init complete");
}

void screen_reset(void) {
  print_string("# SSD1681 software reset");

  spi_send_command(SW_RESET);
  _delay_ms(10);
  spi_wait_for_idle();

  print_string("# SSD1681 reset done");
}

void screen_sleep(void) {
  print_string("# SSD1681 deep sleep...");

  spi_send_command(DEEP_SLEEP_MODE);
  spi_send_data(0x01); // Deep sleep mode 1
  spi_wait_for_idle();

  print_string("# SSD1681 sleep done");
}

void screen_set_memory_area(uint8_t x_start, uint16_t y_start, uint8_t x_end,
                            uint16_t y_end) {
  print_string("# SSD1681 setting memory area");
  print_hex(x_start);
  print_hex(x_end);

  // Set X address range
  spi_send_command(SET_RAM_X_ADDRESS_START_END_POSITION);
  spi_send_data(x_start);
  spi_send_data(x_end);

  // Set Y address range
  spi_send_command(SET_RAM_Y_ADDRESS_START_END_POSITION);
  spi_send_data(y_start & 0xFF);
  spi_send_data((y_start >> 8) & 0xFF);
  spi_send_data(y_end & 0xFF);
  spi_send_data((y_end >> 8) & 0xFF);

  print_string("# SSD1681 memory area set done");
}

void screen_set_memory_pointer(uint8_t x, uint16_t y) {
  print_string("# SSD1681 set memory pointer");
  print_hex(x);
  print_hex(y & 0xFF);

  spi_send_command(SET_RAM_X_ADDRESS_COUNTER);
  spi_send_data(x);

  spi_send_command(SET_RAM_Y_ADDRESS_COUNTER);
  spi_send_data(y & 0xFF);
  spi_send_data((y >> 8) & 0xFF);

  print_string("# SSD1681 set memory pointer done");
}

void screen_clear(uint8_t color) {
  print_string("# SSD1681 clearing screen");
  print_hex(color);

  // Set full screen area (200 px wide = 25 bytes, 200 px tall)
  screen_set_memory_area(0, 0, 24, 199);
  screen_set_memory_pointer(0, 0);

  // Write to RAM
  spi_send_command(WRITE_RAM);

  // Data mode to send pixels
  spi_set_data_mode();
  spi_slave_select_low();

  print_string("# Starting pixel data transmission...");

  // Send 5k bytes (200x200 px / 8 = 5kB)
  for (uint16_t i = 0; i < 5000; i++) {
    SPDR = color;
    while (!(SPSR & (1 << SPIF)))
      ; // Wait for transmission

    // Print progress every 1000 bytes
    if (i % 1000 == 0) {
      print_string("# Progress:");
      print_hex(i / 1000);
    }
  }

  spi_slave_select_high();

  print_string("# SSD1681 screen clear done");
}

void screen_test_pattern(void) {
  print_string("# SSD1681 test pattern");

  // Set full screen
  screen_set_memory_area(0, 0, 24, 199);
  screen_set_memory_pointer(0, 0);

  // Write to RAM
  spi_send_command(WRITE_RAM);

  // Data mode
  spi_set_data_mode();
  spi_slave_select_low();

  print_string("# Starting test pattern transmission...");

  // checkerboard pattern
  for (uint16_t row = 0; row < 200; row++) {
    for (uint8_t col = 0; col < 25; col++) {
      uint8_t pattern;
      if ((row / 10) % 2 == 0) {
        pattern = (col % 2 == 0) ? 0xFF : 0x00; // Alternate black/white
      } else {
        pattern = (col % 2 == 0) ? 0x00 : 0xFF; // Invert
      }

      SPDR = pattern;
      while (!(SPSR & (1 << SPIF)))
        ; // Wait for transmission
    }

    // Print progress every 50 rows
    if (row % 50 == 0) {
      print_string("# Row:");
      print_hex(row);
    }
  }

  spi_slave_select_high();

  print_string("# SSD1681 test pattern done");
}

void screen_update(void) {
  print_string("# SSD1681 screen update");

  // Display update control sequence
  spi_send_command(DISPLAY_UPDATE_CONTROL_2);
  spi_send_data(0xC4); // Enable clock sig, load temperature value, display with
                       // disp mode 1

  // Master activate, triggers update
  spi_send_command(MASTER_ACTIVATION);

  print_string("# Waiting for display update to complete...");
  // Wait for update to finish
  spi_wait_for_idle();

  print_string("# SSD1681 screen update done");
}

void screen_simple_test(void) {
  print_string("# screen_simple_test");

  // Just the top-left corner - 8x8 pixels (1 byte wide, 8 rows)
  screen_set_memory_area(0, 0, 0, 7);
  screen_set_memory_pointer(0, 0);

  spi_send_command(WRITE_RAM);
  spi_set_data_mode();

  // Send 8 bytes of solid black
  spi_slave_select_low();
  for (uint8_t i = 0; i < 8; i++) {
    SPDR = 0xFF; // Solid black
    while (!(SPSR & (1 << SPIF)))
      ;
  }
  spi_slave_select_high();

  print_string("# Simple test data sent");
}
