#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void spi_setup(void);
void spi_slave_select_low(void);
void spi_slave_select_high(void);
void wait_for_idle(void);
void screen_reset(void);
void set_command_mode(void);
void set_data_mode(void);
void spi_transmit(uint8_t);
void send_command(uint8_t command);
void send_data(uint8_t data);

#endif