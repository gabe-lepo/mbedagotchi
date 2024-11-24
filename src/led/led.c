#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

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
   while (1)
   {
      write_led(1);
      _delay_ms(500);
      write_led(0);
      _delay_ms(500);
   }
}