#include "../spi/spi.h"
#include "../ssd1681/ssd1681.h"
#include "../uart/uart.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // Setup UART
  uart_init();
  _delay_ms(100);

  // Setup SPI
  spi_setup();
  _delay_ms(100);

  // Initialize SSD1681
  screen_init();
  _delay_ms(100);

  screen_draw_quarters_simple();

  screen_deinit(); // Must HW reset after this

  return 0;
}
