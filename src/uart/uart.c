#include <avr/io.h>

void uart_init(unsigned int ubrr)
{
   // Set baud rate
   UBRR0H = (unsigned char)(ubrr >> 8);
   UBRR0L = (unsigned char)(ubrr);

   // Enable transmitter
   UCSR0B = (1 << TXEN0);

   // Set frame format: 8 data bits, 1 stop
   UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(unsigned char data)
{
   // Wait for empty transmit buffer
   while (!(UCSR0A & (1 << UDRE0)))
      ;

   UDR0 = data;
}

void print_uart(const char *str)
{
   while (*str)
   {
      uart_transmit(*str++);
   }

   uart_transmit('\r');
   uart_transmit('\n');
}