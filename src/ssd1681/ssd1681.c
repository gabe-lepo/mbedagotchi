#include "ssd1681.h"
#include "../spi/spi.h"
#include "../uart/uart.h"
#include <stdint.h>
#include <util/delay.h>

void screen_init(void) {
  print_string("SSD1681 Initialization - Start");

  // Reset sequence
  spi_hw_reset();
  _delay_ms(10);
  spi_check_busy();

  spi_send_command(SW_RESET);
  _delay_ms(10);
  spi_check_busy();

  // Set gate driver output control
  spi_send_command(DRIVER_OUTPUT_CONTROL);
  spi_send_data(0xC7); // MUX = 199 (200-1)
  spi_send_data(0x00); // MUX high byte
  spi_send_data(0x00); // GD=0, SM=0, TB=0
  _delay_ms(10);

  // Set display RAM size
  spi_send_command(DATA_ENTRY_MODE_SETTING);
  spi_send_data(0x03);
  _delay_ms(10);

  screen_reset_ram();

  // Set panel border
  spi_send_command(BORDER_WAVEFORM_CONTROL);
  spi_send_data(BWC_FOLLOW_LUT0);
  _delay_ms(10);

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

  print_string("SSD1681 Initialization - Done\n");
}

void screen_reset(void) {
  print_string("# SSD1681 software reset");

  spi_send_command(SW_RESET);
  _delay_ms(10);
  spi_check_busy();

  print_string("# SSD1681 reset done\n");
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
  spi_send_command(SET_RAM_X_ADDRESS_COUNTER);
  spi_send_data(x);

  spi_send_command(SET_RAM_Y_ADDRESS_COUNTER);
  spi_send_data(y & 0xFF);
  spi_send_data((y >> 8) & 0xFF);
}

void screen_clear(uint8_t color) {
  print_string("screen_clear_2: start");

  screen_reset_ram();

  spi_send_command(WRITE_RAM_BW);
  spi_set_data_mode();

  spi_slave_select_low();
  for (uint16_t i = 0; i < 5000; i++) {
    spi_transmit(color);
  }
  spi_slave_select_high();
  screen_update();

  print_string("screen_clear_2: done\n");
}

void screen_update(void) {
  print_string("screen_update: start");
  spi_send_command(DISPLAY_UPDATE_CONTROL_1);
  spi_send_data(0x00);
  spi_send_data(0x80);

  spi_send_command(DISPLAY_UPDATE_CONTROL_2);
  // spi_send_data(0xFF); // Max quality, many many flashing
  spi_send_data(0xF7); // Full quality, many flashes
  // spi_send_data(0xC7); // Med quality, less flashing
  // spi_send_data(0x03); // Fast partial update, minimal flashing

  spi_send_command(MASTER_ACTIVATION);

  spi_check_busy();

  print_string("screen_update: done\n");
}

void screen_draw_quarters_simple(void) {
  print_string("screen_draw_quarters_simple: start");

  screen_reset_ram();
  spi_send_command(WRITE_RAM_BW);
  spi_set_data_mode();
  spi_slave_select_low();

  for (uint16_t row = 0; row < 200; row++) {
    for (uint8_t col = 0; col < 25; col++) {
      uint8_t data = COLOR_WHITE;

      if (row % 25 == 0 || col % 5 == 0) {
        data = COLOR_BLACK;
      }

      spi_transmit(data);
    }
  }

  spi_slave_select_high();
  screen_update();

  print_string("screen_draw_quarters_simple: done\n");
}

void screen_reset_ram(void) {
  // Set X and Y start and end positions
  spi_send_command(SET_RAM_X_ADDRESS_START_END_POSITION);
  spi_send_data(0x00);
  spi_send_data(0x18);

  spi_send_command(SET_RAM_Y_ADDRESS_START_END_POSITION);
  spi_send_data(0x00);
  spi_send_data(0x00);
  spi_send_data(0xC7);
  spi_send_data(0x00);

  // Set X and Y address counters
  spi_send_command(SET_RAM_X_ADDRESS_COUNTER);
  spi_send_data(0x00);

  spi_send_command(SET_RAM_Y_ADDRESS_COUNTER);
  spi_send_data(0x00);
  spi_send_data(0x00);
}

void screen_deinit(void) {
  // screen_clear(COLOR_WHITE);
  screen_sleep();
}
