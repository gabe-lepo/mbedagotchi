#include <avr/sleep.h>
#include <avr/io.h>

#include "sleep.h"

int _leftshift(uint8_t bit)
{
   // de-abstraction of _BV()
   return (1 << bit);
}

void setup_sleep(uint8_t mode)
{
   // Clear SMCR bits to reset sleep mode
   SMCR &= ~(_leftshift(SM0) | _leftshift(SM1) | _leftshift(SM2));

   // Might be a good idea to disable interrupts here to prevent any accidental usage of cleared SMCR
   // Clear global interrupt enable bit:
   // cli();

   // Set to IDLE mode
   SMCR |= (mode);

   // Set sleep enable bit (enable sleep)
   SMCR |= (uint8_t)_leftshift(SE);
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
   // sleep_cpu macro is just the AVR sleep instruction, no need to de-abstract
   sleep_cpu();
}