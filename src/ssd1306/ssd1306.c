#include "ssd1306.h"
#include "../spi/spi.h"
#include <util/delay.h>

void ssd1306_init(void) {
  // -----------------
  // BASIC RESET SETUP
  // -----------------

  // HW reset, then sleep. Apparently the screen goes into
  // sleep mode after HW reset, so this may be redundant
  spi_hw_reset();
  spi_send_command(SSD1306_SET_DISP_SLEEP);

  // Horizontal memory addressing mode
  spi_send_command(SSD1306_SET_MEM_ADDR_MODE);
  spi_send_data(SSD1306_MEM_ADDR_MODE_HORIZ);

  // ----------------------
  // HARDWARE CONFIGURATION
  // ----------------------

  // Reset start line
  spi_send_command(SSD1306_SET_DISP_START_LINE(0));

  // Segment remap (normal orientation)
  spi_send_command(SSD1306_SET_SEGMENT_REMAP_COL_0);

  // Set multiplexing ratio for full 64 lines
  spi_send_command(SSD1306_SET_MULTIPLEX_RATIO);
  spi_send_data(SSD1306_MULTIPLEX_RATIO_64);

  // Reset COM output scan direction
  spi_send_command(SSD1306_SET_COM_OUT_SCAN_DIR_RESET);

  // Reset display offset
  spi_send_command(SSD1306_SET_DISP_OFFSET);
  spi_send_data(SSD1306_DISP_OFFSET_RESET);

  // Set COM pin HW config
  spi_send_command(SSD1306_SET_COM_PIN_HW_CONFIG);
  spi_send_data(SSD1306_COM_PIN_CONFIG_ALTERNATING);

  // --------------
  // POWER & TIMING
  // --------------

  // Medium contrast
  spi_send_command(SSD1306_SET_CONTRAST_CTRL);
  spi_send_data(SSD1306_CONTRAST_MID);

  // Display clock divide ratio/osc freq
  spi_send_command(SSD1306_SET_DISP_CLK_DIV_RATIO);
  spi_send_data(SSD1306_CLK_DIV_RATIO_RESET);

  // Pre-charge period
  spi_send_command(SSD1306_SET_PRECHARGE_PERIOD);
  spi_send_data(SSD1306_PRECHARGE_INIT);

  // Set VCOMH deselect level
  spi_send_command(SSD1306_SET_VCOMH_DESELECT_LVL);
  spi_send_data(SSD1306_VCOMH_DESELECT_077_VCC);

  // ----------------
  // DISPLAY BEHAVIOR
  // ----------------

  // Entire disp on with RAM
  spi_send_command(SSD1306_ALL_DISP_ON_FOLLOW_RAM);

  // Non-inverted mode
  spi_send_command(SSD1306_SET_NORMAL_DISP);

  // ------------------
  // DISPLAY ADDRESSING
  // ------------------

  // Set up column and page address ranges (full screen)
  spi_send_command(SSD1306_SET_COL_ADDR);
  spi_send_data(SSD1306_COL_ADDR_START_RESET);
  spi_send_data(SSD1306_COL_ADDR_END_RESET);

  spi_send_command(SSD1306_SET_PAGE_ADDR);
  spi_send_data(SSD1306_PAGE_ADDR_START_RESET);
  spi_send_data(SSD1306_PAGE_ADDR_END_RESET);

  // ------------
  // Done, run it
  // ------------

  // Display on
  spi_send_command(SSD1306_SET_DISP_AWAKE);
  _delay_ms(100);
}
