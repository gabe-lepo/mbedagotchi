#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void spi_setup(void);
void spi_slave_select_low(void);
void spi_slave_select_high(void);
void spi_wait_for_idle(void);
void spi_reset(void);
void spi_set_command_mode(void);
void spi_set_data_mode(void);
void spi_transmit(uint8_t);
void spi_send_command(uint8_t command);
void spi_send_data(uint8_t data);

#endif
