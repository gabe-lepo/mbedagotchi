#ifndef SSD1681_H
#define SSD1681_H

// Screen resolution
#include <stdint.h>
#define DISPLAY_WIDTH 200
#define DISPLAY_HEIGHT 200

// EPD1IN54 commands (from waveshare)
#define DRIVER_OUTPUT_CONTROL 0x01
#define BOOSTER_SOFT_START_CONTROL 0x0C
#define GATE_SCAN_START_POSITION 0x0F
#define DEEP_SLEEP_MODE 0x10
#define DATA_ENTRY_MODE_SETTING 0x11
#define SW_RESET 0x12
#define TEMPERATURE_SENSOR_CONTROL 0x1A
#define MASTER_ACTIVATION 0x20
#define DISPLAY_UPDATE_CONTROL_1 0x21
#define DISPLAY_UPDATE_CONTROL_2 0x22
#define WRITE_RAM 0x24
#define WRITE_VCOM_REGISTER 0x2C
#define WRITE_LUT_REGISTER 0x32
#define SET_DUMMY_LINE_PERIOD 0x3A
#define SET_GATE_TIME 0x3B
#define BORDER_WAVEFORM_CONTROL 0x3C
#define SET_RAM_X_ADDRESS_START_END_POSITION 0x44
#define SET_RAM_Y_ADDRESS_START_END_POSITION 0x45
#define SET_RAM_X_ADDRESS_COUNTER 0x4E
#define SET_RAM_Y_ADDRESS_COUNTER 0x4F
#define TERMINATE_FRAME_READ_WRITE 0xFF

// Colors
#define COLOR_WHITE 0x00
#define COLOR_BLACK 0xFF

// Basic
void screen_init(void);
void screen_reset(void);
void screen_sleep(void);

// Memory controllers
void screen_set_memory_area(uint8_t x_start, uint16_t y_start, uint8_t x_end,
                            uint16_t y_end);
void screen_set_memory_pointer(uint8_t x, uint16_t y);

// Display
void screen_clear(uint8_t color);
void screen_test_pattern(void);
void screen_update(void);

// Debug function
void screen_simple_test(void);

#endif
