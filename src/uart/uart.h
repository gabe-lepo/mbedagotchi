#ifndef UART_H
#define UART_H

#define F_CPU 16000000UL
#define BAUD 9600
#define MY_UBRR F_CPU / 16 / BAUD - 1

void uart_init(unsigned int ubrr);
void uart_transmit(unsigned char data);
void print_string(const char *str);
void print_hex(uint8_t value);

#endif