#include <avr/sleep.h>
#include <avr/io.h>

int _leftshift(bit)
{
   // Arbitration of _BV()
   return (1 << bit);
}

int main(void)
{
   // Breakdown of set_sleep_mode()
   SMCR &= ~(_leftshift(SM0) | _leftshift(SM1) | _leftshift(SM2)); // Clear SMCR bits - This does not trigger any action yet
   // Might be a good idea to disable interrupts here to prevent any accidental usage of cleared SMCR
   SMCR |= (SLEEP_MODE_IDLE); // Set IDLE sleep mode

   // Breakdown of sleep_enable()
   SMCR |= (uint8_t)_leftshift(SE); // Set sleep enable bit

   // sleep_cpu macro is just the AVR sleep instruction, no need to arbitrate
   sleep_cpu();

   return 0;
}