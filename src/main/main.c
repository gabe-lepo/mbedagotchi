#include "../spi/spi.h"
#include "../led/led.h"
#include "../uart/uart.h"
#include "../ssd1681/ssd1681.h"

int main(void)
{
   // UART setup for debugging
   uart_init(MY_UBRR);
   print_string("# UART initialization done");

   // SPI setup
   spi_setup();

   // Screen setup
   reset();
   screen_init();

   // Draw something

   // Sleep
   screen_sleep();
   led_blink(5);
   // screen_reset();
   // led_blink_continuous();

   return 1;
}