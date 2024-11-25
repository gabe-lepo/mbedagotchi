#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

#include "../uart/uart.h"

#define LED_PIN PB5

void led_init(void)
{
   DDRB |= (1 << LED_PIN);
}

void write_led(uint8_t flag)
{
   if (flag)
   {
      PORTB |= (1 << LED_PIN);
   }
   else
   {
      PORTB &= ~(1 << LED_PIN);
   }
}

void led_blink(uint8_t count)
{
   print_string("# LED - Blinking");
   // print_hex_8bit(count);
   led_init();
   uint8_t iter = 0;
   while (iter <= count)
   {
      write_led(1);
      _delay_ms(50);
      write_led(0);
      _delay_ms(50);
      iter++;
   }
}

void led_blink_continuous(void)
{
   led_init();
   while (1)
   {
      write_led(1);
      _delay_ms(500);
      write_led(0);
      _delay_ms(500);
   }
}