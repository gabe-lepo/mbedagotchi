#include "ssd1681.h"
#include "../spi/spi.h"
#include "../uart/uart.h"
#include <stdint.h>
#include <util/delay.h>

// TODO: Figure out how to write full-screen buffer to flash?
// cant store all 5kB in RAM (2kB max)
// static uint8_t screen_buffer[5000]; // Doesnt fit in 2kB RAM

#define TILE_SIZE 50
#define TILES_X 200 / TILE_SIZE
#define TILES_Y 200 / TILE_SIZE
#define TILE_BUFFER_SIZE (TILE_SIZE * TILE_SIZE / 8)

static uint8_t tile_buffer[TILE_BUFFER_SIZE];

void tile_buffer_clear(uint8_t color) {
  for (uint16_t i = 0; i < TILE_BUFFER_SIZE; i++) {
    tile_buffer[i] = color;
  }
}

void tile_buffer_set_px(uint16_t tile_x, uint16_t tile_y, uint8_t color) {
  if (tile_x >= TILE_SIZE || tile_y >= TILE_SIZE) {
    return;
  }

  uint16_t col = tile_x / 8;    // Which byte (column)
  uint8_t bit_pos = tile_x % 8; // Which bit in the byte
  uint16_t index = (tile_y * (TILE_SIZE / 8)) + col;

  if (color == COLOR_BLACK) {
    // Clear bit (0x00)
    tile_buffer[index] &= ~(1 << (7 - bit_pos));
  } else {
    // Set bit (0xFF)
    tile_buffer[index] |= (1 << (7 - bit_pos));
  }
}

void tile_buffer_send_to_screen(uint8_t tile_col, uint8_t tile_row) {
  print_string("tile_buffer_send_to_screen");

  uint8_t screen_x_start = tile_col * (TILE_SIZE / 8);
  uint8_t screen_x_end = screen_x_start + (TILE_SIZE / 8) - 1;
  uint8_t screen_y_start = tile_row * TILE_SIZE;
  uint8_t screen_y_end = screen_y_start + TILE_SIZE - 1;

  screen_set_memory_area(screen_x_start, screen_y_start, screen_x_end,
                         screen_y_end);
  screen_set_memory_pointer(screen_x_start, screen_y_start);

  spi_send_command(WRITE_RAM_BW);
  spi_set_data_mode();
  spi_slave_select_low();

  for (uint16_t i = 0; i < TILE_BUFFER_SIZE; i++) {
    spi_transmit(tile_buffer[i]);
  }

  spi_slave_select_high();
}

void screen_init(void) {
  print_string("screen_init");

  // Reset sequence
  spi_hw_reset();
  spi_send_command(SW_RESET);
  _delay_ms(10);

  // Set gate driver output control
  spi_send_command(DRIVER_OUTPUT_CONTROL);
  spi_send_data(0xC7); // MUX = 199 (200-1)
  spi_send_data(0x00); // MUX high byte
  spi_send_data(0x00); // GD=0, SM=0, TB=0
  _delay_ms(10);

  // Set display RAM size
  spi_send_command(DATA_ENTRY_MODE_SETTING);
  spi_send_data(0x03); // Y increment and X increment

  // Reset ram size and address counter
  // Set X address range
  spi_send_command(SET_RAM_X_ADDRESS_START_END_POSITION);
  spi_send_data(0x00);
  spi_send_data(0x18);

  // Set Y address range
  spi_send_command(SET_RAM_Y_ADDRESS_START_END_POSITION);
  spi_send_data(0x00);
  spi_send_data(0x00);
  spi_send_data(0xC7);
  spi_send_data(0x00);

  // Set panel border
  // spi_send_command(BORDER_WAVEFORM_CONTROL);
  /*
  VSS = Low voltage (black pixels?)
  VSL = Negative voltage (stronger black px push)
  VSH1 = Positive V (white pixels?)
  VSH2 = String positive V (stronger white)
  */
  // Fixed level, VSH2, no GS transition control, no GS transition for VBD:
  // spi_send_data(0x70);
  // Fixed level, VSH1, no GS transition control, no GS transition for VBD:
  // spi_send_data(0x50);
  // _delay_ms(10);

  // Load waveform LUT
  // TS controls
  spi_send_command(TEMPERATURE_SENSOR_CONTROL);
  spi_send_data(0x80); // Internal temp sensor
  _delay_ms(10);

  // Load waveform LUT from OTP
  spi_send_command(DISPLAY_UPDATE_CONTROL_2);
  spi_send_data(0xF7); // Load LUT from OTP

  spi_send_command(MASTER_ACTIVATION);
  spi_check_busy();

  spi_send_command(BORDER_WAVEFORM_CONTROL);
  spi_send_data(0x50);
  // spi_send_data(0x54);

  // Booster soft start (PS stabilization)
  spi_send_command(BOOSTER_SOFT_START_CONTROL);
  spi_send_data(0xD7);
  spi_send_data(0xD6);
  spi_send_data(0x9D);
  _delay_ms(10);

  // Optional: VCOM setting for better contrast
  spi_send_command(WRITE_VCOM_REGISTER);
  spi_send_data(0xA8); // -2.0V (typical setting)
  _delay_ms(10);
}

void screen_reset(void) {
  print_string("screen_reset");

  spi_send_command(SW_RESET);
  _delay_ms(10);
  spi_check_busy();
}

void screen_sleep(void) {
  print_string("screen_sleep");
  spi_send_command(DEEP_SLEEP_MODE);
  spi_send_data(DSM_2_DELETE_RAM);
}

void screen_set_memory_area(uint8_t x_start, uint16_t y_start, uint8_t x_end,
                            uint16_t y_end) {
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
}

void screen_set_memory_pointer(uint8_t x, uint16_t y) {
  print_string("screen_set_memory_pointer");

  spi_send_command(SET_RAM_X_ADDRESS_COUNTER);
  spi_send_data(x);

  spi_send_command(SET_RAM_Y_ADDRESS_COUNTER);
  spi_send_data(y & 0xFF);
  spi_send_data((y >> 8) & 0xFF);
}

void screen_clear(uint8_t color) {
  print_string("screen_clear");

  screen_set_memory_pointer(0, 0);

  spi_send_command(WRITE_RAM_BW);
  spi_set_data_mode();

  spi_slave_select_low();
  for (uint16_t i = 0; i < 5000; i++) {
    spi_transmit(color);
  }
  spi_slave_select_high();
  screen_update();
}

void screen_update(void) {
  print_string("screen_update");

  spi_send_command(DISPLAY_UPDATE_CONTROL_1);
  spi_send_data(0x00);

  spi_send_command(DISPLAY_UPDATE_CONTROL_2);
  // Enable clock, enable analog, display mode 1, enable analog, disable OSC
  spi_send_data(0xC7);
  // spi_send_data(0xCF);

  spi_send_command(MASTER_ACTIVATION);
  spi_check_busy();
}

void screen_reset_ram(void) {
  screen_set_memory_area(0, 0, 24, 199);
  screen_set_memory_pointer(0, 0);
}

void screen_draw_lines(void) {
  print_string("screen_draw_squares");

  screen_reset_ram();
  spi_send_command(WRITE_RAM_BW);
  spi_set_data_mode();
  spi_slave_select_low();

  for (uint16_t row = 0; row <= 199; row++) {
    for (uint16_t col = 0; col <= 24; col++) {
      uint8_t data = COLOR_WHITE;

      if (col % 2 == 0) {
        data = COLOR_BLACK;
      }

      spi_transmit(data);
    }
  }

  spi_slave_select_high();
  screen_update();
}

void screen_draw_radial(uint16_t ring_spacing) {
  print_string("screen_draw_radial");

  screen_reset_ram();
  spi_send_command(WRITE_RAM_BW);
  spi_set_data_mode();
  spi_slave_select_low();

  // Params
  int16_t center_row = 100;
  uint16_t center_col = 12;
  int16_t resolution = 1028;

  for (uint16_t row = 0; row <= 199; row++) {
    for (uint16_t col = 0; col <= 24; col++) {
      uint8_t data = COLOR_BLACK;

      int16_t dist_row = (int16_t)row - center_row;
      int16_t dist_col = (int16_t)col - center_col;
      uint16_t dist_sq =
          (dist_row * dist_row) + (dist_col * dist_col * resolution);

      if ((dist_sq / ring_spacing) % 2 == 0) {
        data = COLOR_WHITE;
      }

      spi_transmit(data);
    }
  }

  spi_slave_select_high();
  screen_update();
}

void screen_draw_radial_tiles(void) {
  print_string("screen_draw_radial_tiles");

  // Pattern pararms
  int16_t center_x = 100;
  int16_t center_y = 100;
  int16_t resolution = 16;
  int16_t ring_spacing = 500;

  // Process each tile
  for (uint8_t tile_row = 0; tile_row < TILES_Y; tile_row++) {
    for (uint8_t tile_col = 0; tile_col < TILES_X; tile_col++) {
      // print_string("Processing tile:");
      // print_hex(tile_row * TILES_X + tile_col);

      tile_buffer_clear(COLOR_WHITE);

      uint16_t tile_screen_x = tile_col * TILE_SIZE;
      uint16_t tile_screen_y = tile_row * TILE_SIZE;

      // Draw the pattern for this tile
      for (uint8_t local_y = 0; local_y < TILE_SIZE; local_y++) {
        for (uint8_t local_x = 0; local_x < TILE_SIZE; local_x++) {
          // Get global screen coords
          uint16_t global_x = tile_screen_x + local_x;
          uint16_t global_y = tile_screen_y + local_y;

          // Skip if we manage to go outside screen bounds
          if (global_x >= 200 || global_y >= 200)
            continue;

          // Get distance from center
          int16_t dist_x = (int16_t)global_x - center_x;
          int16_t dist_y = (int16_t)global_y - center_y;
          uint32_t dist_squared = (uint32_t)(dist_x * dist_x) +
                                  (uint32_t)(dist_y * dist_y * resolution);

          // Create the rings
          if ((dist_squared / ring_spacing) % 2 == 0) {
            tile_buffer_set_px(local_x, local_y, COLOR_BLACK);
          }
        }
      }

      tile_buffer_send_to_screen(tile_col, tile_row);
    }
  }

  screen_reset_ram();
  screen_update();
}
