#ifndef SLEEP_H
#define SLEEP_H

void init_sleep_led();
void setup_sleep(uint8_t mode);
void update_sleep_led();
void setup_sleep_idle();
void setup_sleep_pwr_down();
void enter_sleep();

#endif