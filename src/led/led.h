#ifndef LED_H
#define LED_H

#include <stdint.h>

void led_init(void);
void led_on(void);
void led_off(void);
void led_blink(uint16_t num_blink);

#endif
