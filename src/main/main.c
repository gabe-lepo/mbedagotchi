#include "../spi/spi.h"
#include "../ssd1681/ssd1681.h"
#include "../uart/uart.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  uart_init();
  _delay_ms(100);

  spi_setup();
  _delay_ms(100);

  screen_init();
  _delay_ms(100);

  // Test 1: Simple test - try to show just a small black square
  print_string("=== TEST 1: Simple Black Square ===");
  screen_simple_test();
  screen_update();
  print_string("Simple test complete - check top-left corner");
  _delay_ms(5000);

  // Test 2: Try clearing to black (most obvious)
  // print_string("=== TEST 2: Clear to Black ===");
  // screen_clear(COLOR_BLACK);
  // screen_update();
  // print_string("Black clear complete - entire screen should be black");
  // _delay_ms(5000);

  // Test 3: Clear to white
  // print_string("=== TEST 3: Clear to White ===");
  // screen_clear(COLOR_WHITE);
  // screen_update();
  // print_string("White clear complete - entire screen should be white");
  // _delay_ms(5000);

  // Test 4: Test pattern
  // print_string("=== TEST 4: Test Pattern ===");
  // screen_test_pattern();
  // screen_update();
  // print_string("Test pattern complete - should see checkerboard");
  // _delay_ms(5000);

  // Test 5: Try different update sequence
  // print_string("=== TEST 5: Alternative Update Method ===");
  // screen_clear(COLOR_BLACK);

  // Try a different update sequence
  // print_string("Trying different update sequence...");
  // spi_send_command(DISPLAY_UPDATE_CONTROL_1);
  // spi_send_data(0x00);
  // spi_send_data(0x80);

  // spi_send_command(DISPLAY_UPDATE_CONTROL_2);
  // spi_send_data(0xF7); // Different update mode

  // spi_send_command(MASTER_ACTIVATION);
  // spi_wait_for_idle();

  // print_string("Alternative update complete");
  // _delay_ms(5000);

  // print_string("=== ALL TESTS COMPLETE ===");

  // Sleep
  print_string("Putting display to sleep...");
  screen_sleep();

  print_string("Test program finished!");
  return 0;
}
