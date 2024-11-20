#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void spi_setup(void);
void spi_slave_select_low(void);
void spi_slave_select_high(void);
void spi_transmit(uint8_t);

#endif