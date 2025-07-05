#ifndef SSD1306_H
#define SSD1306_H

/* ===========================================
 * SSD1306 OLED Display Driver Commands & Data
 * ===========================================
 */

// ===========================================
// 1. FUNDAMENTALS
// ===========================================
#define SSD1306_SET_CONTRAST_CTRL 0x81
#define SSD1306_CONTRAST_MIN 0x00
#define SSD1306_CONTRAST_MID 0x7F
#define SSD1306_CONTRAST_MAX 0xFF

#define SSD1306_ALL_DISP_ON_FOLLOW_RAM 0xA4
#define SSD1306_ALL_DISP_ON_IGNORE_RAM 0xA5

#define SSD1306_SET_NORMAL_DISP 0xA6
#define SSD1306_SET_INVERSE_DISP 0xA7

#define SSD1306_SET_DISP_SLEEP 0xAE
#define SSD1306_SET_DISP_AWAKE 0xAF

// ===========================================
// 2. SCROLLING
// ===========================================
#define SSD1306_HORIZ_SCROLL_SETUP_RIGHT 0x26
#define SSD1306_HORIZ_SCROLL_SETUP_LEFT 0x27
#define SSD1306_VERTI_HORIZ_SCROLL_RIGHT 0x29
#define SSD1306_VERTI_HORIZ_SCROLL_LEFT 0x2A
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_SET_VERTI_SCROLL_AREA 0xA3

// Scroll timing intervals
#define SSD1306_SCROLL_2_FRAMES 0x07
#define SSD1306_SCROLL_3_FRAMES 0x04
#define SSD1306_SCROLL_4_FRAMES 0x05
#define SSD1306_SCROLL_5_FRAMES 0x00
#define SSD1306_SCROLL_25_FRAMES 0x06
#define SSD1306_SCROLL_64_FRAMES 0x01
#define SSD1306_SCROLL_128_FRAMES 0x02
#define SSD1306_SCROLL_256_FRAMES 0x03

// Page addresses for scrolling
#define SSD1306_PAGE_0 0x00
#define SSD1306_PAGE_1 0x01
#define SSD1306_PAGE_2 0x02
#define SSD1306_PAGE_3 0x03
#define SSD1306_PAGE_4 0x04
#define SSD1306_PAGE_5 0x05
#define SSD1306_PAGE_6 0x06
#define SSD1306_PAGE_7 0x07

// ===========================================
// 3. ADDRESSING SETTINGS
// ===========================================
#define SSD1306_SET_MEM_ADDR_MODE 0x20
#define SSD1306_MEM_ADDR_MODE_HORIZ 0x00
#define SSD1306_MEM_ADDR_MODE_VERTI 0x01
#define SSD1306_MEM_ADDR_MODE_PAGE 0x02

#define SSD1306_SET_COL_ADDR 0x21
#define SSD1306_COL_ADDR_START_RESET 0x00
#define SSD1306_COL_ADDR_END_RESET 0x7F

#define SSD1306_SET_PAGE_ADDR 0x22
#define SSD1306_PAGE_ADDR_START_RESET 0x00
#define SSD1306_PAGE_ADDR_END_RESET 0x07

// Page addressing mode commands (not using these)
#define SSD1306_SET_LOWER_COL(x) (0x00 | ((x) & 0x0F))
#define SSD1306_SET_HIGHER_COL(x) (0x10 | ((x) & 0x0F))
#define SSD1306_SET_PAGE_START(x) (0xB0 | ((x) & 0x07))

// ===========================================
// 4. HARDWARE CONFIGS
// ===========================================
#define SSD1306_SET_DISP_START_LINE(line) (0x40 | ((line) & 0x3F))
#define SSD1306_SET_DISP_START_LINE_RESET 0x40

#define SSD1306_SET_SEGMENT_REMAP_COL_0 0xA0
#define SSD1306_SET_SEGMENT_REMAP_COL_127 0xA1

#define SSD1306_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_MULTIPLEX_RATIO_64 0x3F
#define SSD1306_MULTIPLEX_RATIO_32 0x1F
#define SSD1306_MULTIPLEX_RATIO_16 0x0F

#define SSD1306_SET_COM_OUT_SCAN_DIR_RESET 0xC0
#define SSD1306_SET_COM_OUT_SCAN_DIR_REMAP 0xC8

#define SSD1306_SET_DISP_OFFSET 0xD3
#define SSD1306_DISP_OFFSET_RESET 0x00

#define SSD1306_SET_COM_PIN_HW_CONFIG 0xDA
#define SSD1306_COM_PIN_CONFIG_SEQUENTIAL 0x02
#define SSD1306_COM_PIN_CONFIG_ALTERNATIVE 0x12
#define SSD1306_COM_PIN_CONFIG_ALT_REMAP 0x32

// ===========================================
// 5. TIMING & DRIVING SCHEME
// ===========================================
#define SSD1306_SET_DISP_CLK_DIV_RATIO 0xD5
#define SSD1306_CLK_DIV_RATIO_RESET 0x80

#define SSD1306_SET_PRECHARGE_PERIOD 0xD9
#define SSD1306_PRECHARGE_PERIOD_RESET 0x22

#define SSD1306_SET_VCOMH_DESELECT_LVL 0xDB
#define SSD1306_VCOMH_DESELECT_065_VCC 0x00
#define SSD1306_VCOMH_DESELECT_077_VCC 0x20
#define SSD1306_VCOMH_DESELECT_083_VCC 0x30

#define SSD1306_NOP 0xE3

// ===========================================
// DISPLAY SPECS
// ===========================================
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_PAGES 8
#define SSD1306_BUF_SIZE 1024

// ===========================================
// INIT SEQUENCE HELPERS
// ===========================================
#define SSD1306_INIT_MULTIPLEX_RATIO SSD1306_MULTIPLEX_RATIO_64
#define SSD1306_INIT_COM_PIN_CONFIG SSD1306_COM_PIN_CONFIG_ALTERNATIVE
#define SSD1306_INIT_CONTRAST SSD1306_CONTRAST_MID
#define SSD1306_INIT_PRECHARGE 0xF1
#define SSD1306_INIT_VCOMH SSD1306_VCOMH_DESELECT_077_VCC

// ===========================================
// Function protos
// ===========================================

void ssd1306_init(void);

#endif
