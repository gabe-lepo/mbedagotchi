#ifndef SLEEP_H
#define SLEEP_H

int _leftshift(uint8_t bit);
void setup_sleep(uint8_t mode);
void setup_sleep_idle();
void setup_sleep_pwr_down();
void enter_sleep();

#endif