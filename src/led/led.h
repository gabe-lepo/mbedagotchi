#ifndef LED_H
#define LED_H

#include <stdint.h>

void led_init(void);
void write_led(uint8_t flag);
void led_blink(uint8_t count);
void led_blink_continuous(void);

#endif