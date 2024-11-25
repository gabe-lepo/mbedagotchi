#include <avr/io.h>

#include <stdlib.h>

/**
 * @brief UART setup function
 *
 * @param ubrr
 */
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

/**
 * @brief Write to UART data register
 *
 * @param data
 */
void uart_transmit(unsigned char data)
{
   // Wait for empty transmit buffer
   while (!(UCSR0A & (1 << UDRE0)))
      ;

   UDR0 = data;
}

/**
 * @brief Simple print function with automatic newline and carriage returns
 *
 * @param str String pointer to print
 */
void print_string(const char *str)
{
   while (*str)
   {
      uart_transmit(*str++);
   }

   uart_transmit('\r');
   uart_transmit('\n');
}

/**
 * @brief Format print hex values (8 bit buffer)
 *
 * @param value Number to print
 */
void print_hex(uint8_t value)
{
   // '\t', '0', 'x', 2 hex digits, and '\0'
   char buffer[7];
   buffer[0] = '\t';
   buffer[1] = '0';
   buffer[2] = 'x';

   // Convert to hex, add leading zero if needed, buffer
   if (value < 0x10)
   {
      buffer[3] = '0';
      itoa(value, &buffer[4], 16);
   }
   else
   {
      itoa(value, &buffer[3], 16);
   }
   buffer[5] = '\0';

   print_string(buffer);
}