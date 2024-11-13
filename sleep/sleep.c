#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/delay.h>

#include "sleep.h"

#define SLEEP_LED_PIN PORTD2

// Set PORTD pin 2 as output
void init_sleep_led()
{
   DDRD |= (1 << SLEEP_LED_PIN);
}

void setup_sleep(uint8_t mode)
{
   // Setup sleep LED
   init_sleep_led();

   // Clear SMCR bits to reset sleep mode
   SMCR &= ~((1 << SM0) | (1 << SM1) | (1 << SM2));

   // Might be a good idea to disable interrupts here to prevent any accidental usage of cleared SMCR
   // Clear global interrupt enable bit:
   // cli();

   // Set to IDLE mode
   SMCR |= (mode);

   // Set sleep enable bit (enable sleep)
   SMCR |= (1 << SE);
}

// Set LED behavior: ON when SMCR doesnt have SE, OFF when SMCR has SE bit set
void update_sleep_led()
{
   // Check if SMCR has SE bit
   if (SMCR & (1 << SE))
   {
      // Sleep enable active - LED OFF
      PORTD &= ~(1 << SLEEP_LED_PIN);
   }
   else
   {
      // SMCR doesnt have SE bit set - LED ON
      PORTD |= (1 << SLEEP_LED_PIN);
   }
}

void setup_sleep_idle()
{
   setup_sleep(SLEEP_MODE_IDLE);
}

void setup_sleep_pwr_down()
{
   setup_sleep(SLEEP_MODE_PWR_DOWN);
}

void enter_sleep()
{
   // No need to de-abstract, this macro uses the ASM sleep instruction directly
   sleep_cpu();
}