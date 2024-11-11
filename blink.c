#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PORTB5 // 00X0 0000

int main(void)
{
   unsigned int counter;
   DDRB |= (1 << LED_PIN);

   do
   {
      counter = 1;
      PORTB &= ~(1 << LED_PIN); // Ensure LED bit is off

      PORTB ^= (1 << LED_PIN); // LED BIT FLIP - ON
      _delay_ms(500);
      PORTB ^= (1 << LED_PIN); // LED BIT FLIP - OFF
      _delay_ms(500);

      counter++;
   } while (counter <= 10);

   return 0;
}