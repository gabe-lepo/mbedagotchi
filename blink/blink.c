#include <avr/io.h>
#include <util/delay.h>
#include <sys/types.h>

#define LED_PIN PORTB5
#define BLINK_TIME_MS 1000

int main(void)
{
   unsigned int counter = 1;
   // Set data direction register for port B pin 5 to OUT
   DDRB |= (1 << LED_PIN);

   do
   {
      // Ensure LED bit is off by AND assigning the inverse of 1<<5
      PORTB &= ~(1 << LED_PIN);

      // Flip the PORTB pin 5 led bit (it should be 0 after the previous PORTB line)
      PORTB ^= (1 << LED_PIN);
      _delay_ms(BLINK_TIME_MS / 2);
      // Flip the PORTB pin 5 led bit (it should be 1 after the previous PORTB line)
      PORTB ^= (1 << LED_PIN);
      _delay_ms(BLINK_TIME_MS / 2);

      counter++;
   } while (counter <= 10);

   return 0;
}