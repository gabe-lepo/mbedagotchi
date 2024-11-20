/*
   Links:
   * https://www.microcenter.com/product/632695/inland-154-inch-e-ink-lcd-display-screen

   Datasheet notes:
   * PRSPI bit may need to 0 to enable SPI, but this may only be for USART>SPI control...
   * SPI master inits comm cycle when slave-select pin is pulled low
      * Then master/slave prepare packet data in shift registers
      * Master generates required SCK signal
   * After each data packet, master syncs slave by pulling SS high
   * No automatic control of SS when master
   * Writing byte to SPI DR starts SCK generator, then 8 bits shifted to slave
      * After shifting 1 byte, SCK generator stops and sets EOT flag in SPIF
   * Request interrupt by setting SPIE bit in SPCR
   * Continue to shift more bytes, or if done, signal end of packet with SS high
      * Last byte is kept in buffer register for later
   * Single buffer for transmit as master, must wait for shift cycle to complete before next byte in SPDR
   *

   Board function Board/CPU         Screen function         Screen data direction
   ------------------------------------------------------------------------------
   SS             D10 -> PB2  -->   CS    (chip select)     [IN]
   MOSI           D11 -> PB3  -->   SDI   (serial data in)  [IN]
   MISO           D12 -> PB4  xxx   xxx   (unused)
   SCK            D13 -> PB5  -->   CLK   (clock)           [IN]

   OC1A           D9  -> PB1  -->   D/C   (data/command)    [IN]
   CLK/CP1        D8  -> PB0  -->   RES   (reset)           [IN]
   xxx            D2  -> PD2  -->   BUSY  (busy)            [OUT]
*/

#include <avr/io.h>

#define SS_PIN PB2
#define MOSI_PIN PB3
#define SCK_PIN PB5
#define DC_PIN PB1
#define RESET_PIN PB0
#define BUSY_PIN PD2

void spi_setup(void)
{
   // Set our PORTB pins as outs
   DDRB |= (1 << SS_PIN) | (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << DC_PIN) | (1 << RESET_PIN);

   // Set the PORTD pin as in for screen's BUSY signal
   DDRD &= ~(1 << BUSY_PIN);

   //     Enable SPI | Set master | Set clock rate fck/16 and CPOL/CPHA as 0
   SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);

   // Ensure SPI2X is not set, so we dont double the SCK rate
   if (SPSR & (1 << SPI2X))
   {
      // Bit is set, clear it
      SPSR &= ~(1 << SPI2X);
   }
   else
   {
      // Default case - intentionally empty
   }

   // Ensure DORD is not set, so we send MSB first. May have to set this to do LSB -- not sure yet
   if (SPCR & (1 << DORD))
   {
      // Bit is set, clear it to force MSB first
      SPCR &= ~(1 << DORD);
   }
   else
   {
      // Default case - intentionally empty
   }
}

void spi_slave_select_low(void)
{
   // SS low to enable data transmission
   PORTB &= ~(1 << SS_PIN);
}

void spi_slave_select_high(void)
{
   // SS high when done with data transmission
   PORTB |= (1 << SS_PIN);
}

void spi_transmit(uint8_t data)
{
   SPDR = data;
   while (!(SPSR & (1 << SPIF)))
      ;
}

int main(void)
{
   spi_mosi_setup();

   while (1)
   {
   }

   return 1;
}