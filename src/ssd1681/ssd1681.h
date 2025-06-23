#ifndef SSD1681_H
#define SSD1681_H

#include <stdint.h>

// Screen resolution
#define DISPLAY_WIDTH 200
#define DISPLAY_HEIGHT 200

// Colors
#define COLOR_WHITE 0xFF
#define COLOR_BLACK 0x00

// Commands
#define DRIVER_OUTPUT_CONTROL 0x01
#define GATE_DRIVING_VOLTAGE_CONTROL 0x03
#define SOURCE_DRIVING_VOLTAGE_CONTROL 0x04
#define INITIAL_CODE_SETTING_OTP_PROGRAM 0x08
#define WRITE_REGISTER_INITIAL_CODE_SETTING 0x09
#define READ_REGISTER_INITIAL_CODE_SETTING 0x0A
#define BOOSTER_SOFT_START_CONTROL 0x0C
#define DEEP_SLEEP_MODE 0x10
#define DATA_ENTRY_MODE_SETTING 0x11
#define SW_RESET 0x12
#define HV_READY_DETECTION 0x14
#define VCI_DETECTION 0x15
#define TEMPERATURE_SENSOR_CONTROL 0x18
#define TEMPERATURE_SENSOR_CONTROL_WRITE 0x1A
#define TEMPERATURE_SENSOR_CONTROL_READ 0x1B
#define TEMPERATURE_SENSOR_CONTROL_WRITE_EXT 0x1C
#define MASTER_ACTIVATION 0x20
#define DISPLAY_UPDATE_CONTROL_1 0x21
#define DISPLAY_UPDATE_CONTROL_2 0x22
#define WRITE_RAM_BW 0x24
#define WRITE_RAM_RED 0x26
#define READ_RAM 0x27
#define VCOM_SENSE 0x28
#define VCOM_SENSE_DURATION 0x29
#define PROGRAM_VCOM_OTP 0x2A
#define WRITE_REG_VCOM_CONTROL 0x2B
#define WRITE_VCOM_REGISTER 0x2C
#define OTP_REG_READ_DISPLAY_OPTION 0x2D
#define USER_ID_READ 0x2E
#define STATUS_BIT_READ 0x2F
#define PROGRAM_WS_OTP 0x30
#define LOAD_WS_OTP 0x31
#define WRITE_LUT_REGISTER 0x32
#define CRC_CALC 0x34
#define CRC_STATUS_READ 0x35
#define PROGRAM_OTP_SELECT 0x36
#define WRITE_REG_DISPLAY_OPTION 0x37
#define WRITE_REG_USER_ID 0x38
#define OTP_PROGRAM_MODE 0x39
#define BORDER_WAVEFORM_CONTROL 0x3C
#define END_OPT 0x3F
#define READ_RAM_OPT 0x41
#define SET_RAM_X_ADDRESS_START_END_POSITION 0x44
#define SET_RAM_Y_ADDRESS_START_END_POSITION 0x45
#define AUTO_WRITE_RED_RAM_REGULAR_PATTERN 0x46
#define AUTO_WRITE_BW_RAM_REGULAR_PATTERN 0x47
#define SET_RAM_X_ADDRESS_COUNTER 0x4E
#define SET_RAM_Y_ADDRESS_COUNTER 0x4F
#define NOP_TERM_FRAME_READ_WRTIE 0x7F

// Data
#define DSM_1_RETAIN_RAM 0x01
#define DSM_2_DELETE_RAM 0x11
#define BWC_WHITE_FIXED 0x50
#define BWC_BLACK_FIXED 0x40
#define BWC_FOLLOW_LUT0 0x04
#define BWC_FOLLOW_LUT1 0x05
#define BWC_FLOATING 0xC0
#define BWC_VCOM 0x80

// Basic controls
void screen_init(void);
void screen_reset(void);
void screen_sleep(void);
void screen_update(void);
void screen_clear(uint8_t color);

// Memory controllers
void screen_set_memory_area(uint8_t x_start, uint16_t y_start, uint8_t x_end,
                            uint16_t y_end);
void screen_set_memory_pointer(uint8_t x, uint16_t y);
void screen_reset_ram(void);

// Draw
void screen_draw_lines(void);
void screen_draw_radial(void);

#endif
