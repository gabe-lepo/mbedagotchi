#include "../spi/spi.h"
#include "../uart/uart.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // UART setup
  uart_init();
  _delay_ms(100);

  print_string("=== SPI FUNCTIONALITY TEST ===");

  // Test SPI setup
  spi_setup();

  // Test reset
  spi_reset();

  // Test command sending
  spi_send_command(0x12); // Software reset

  // Test wait for idle
  spi_wait_for_idle();

  print_string("=== SPI TEST PASSED ===");

  return 0;
}
