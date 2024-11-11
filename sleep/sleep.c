#include <avr/sleep.h>

int main(void)
{
   set_sleep_mode(SLEEP_MODE_IDLE);
   sleep_enable();
   sleep_cpu();

   return 0;
}