#include "../led/led.h"
#include "../spi/spi.h"
#include "../ssd1681/ssd1681.h"
#include "../uart/uart.h"
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void init(void) {
  led_init();
  uart_init();
  spi_setup();
  screen_init();
}

int main(void) {
  init();

  // screen_clear(COLOR_WHITE);

  for (uint16_t ring_spacing = 100; ring_spacing < 10000; ring_spacing += 2) {
    screen_draw_radial(ring_spacing);
    _delay_ms(200);
  }

  screen_sleep(); // Must HW reset after this

  while (1) {
    led_on();
    _delay_ms(500);
    led_off();
    _delay_ms(500);
  }

  return 0;
}
