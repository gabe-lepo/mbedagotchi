#include "../led/led.h"
#include "../spi/spi.h"
#include "../ssd1681/ssd1681.h"
#include "../uart/uart.h"
#include <avr/io.h>
#include <util/delay.h>

void init(void) {
  led_init();
  led_on();
  uart_init();
  spi_setup();
  screen_init();
  led_off();
}

int main(void) {
  init();

  led_on();
  screen_clear(COLOR_WHITE);
  led_off();

  led_on();
  screen_draw_radial();
  led_off();

  screen_sleep(); // Must HW reset after this

  while (1) {
    led_on();
    _delay_ms(500);
    led_off();
    _delay_ms(500);
  }

  return 0;
}
