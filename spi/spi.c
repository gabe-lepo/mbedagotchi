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

   Steps:
   1. Set clock polarity (CPOL) and phase (CPHA)
      a. Figure out clock speed requirement for screen
   2. Set MOSI and SCK pins as outs

*/

#include <avr/io.h>

#define SS_PIN PB2
#define MOSI_PIN PB3
#define SCK_PIN PB5
#define DC_PIN PB1
#define RESET_PIN PB0
#define BUSY_PIN PD2

int main(void)
{

   return 1;
}