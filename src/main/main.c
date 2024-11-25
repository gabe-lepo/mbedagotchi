#include "../spi/spi.h"
#include "../led/led.h"
#include "../uart/uart.h"

// Display resolution
#define EPD_WIDTH 200
#define EPD_HEIGHT 200

// EPD1IN54 commands
#define DRIVER_OUTPUT_CONTROL 0x01
#define BOOSTER_SOFT_START_CONTROL 0x0C
#define GATE_SCAN_START_POSITION 0x0F
#define DEEP_SLEEP_MODE 0x10
#define DATA_ENTRY_MODE_SETTING 0x11
#define SW_RESET 0x12
#define TEMPERATURE_SENSOR_CONTROL 0x1A
#define MASTER_ACTIVATION 0x20
#define DISPLAY_UPDATE_CONTROL_1 0x21
#define DISPLAY_UPDATE_CONTROL_2 0x22
#define WRITE_RAM 0x24
#define WRITE_VCOM_REGISTER 0x2C
#define WRITE_LUT_REGISTER 0x32
#define SET_DUMMY_LINE_PERIOD 0x3A
#define SET_GATE_TIME 0x3B
#define BORDER_WAVEFORM_CONTROL 0x3C
#define SET_RAM_X_ADDRESS_START_END_POSITION 0x44
#define SET_RAM_Y_ADDRESS_START_END_POSITION 0x45
#define SET_RAM_X_ADDRESS_COUNTER 0x4E
#define SET_RAM_Y_ADDRESS_COUNTER 0x4F
#define TERMINATE_FRAME_READ_WRITE 0xFF

int main(void)
{
   // UART setup for debugging
   uart_init(MY_UBRR);
   print_string("# UART initialization done");

   // SPI setup
   spi_setup();

   // Screen setup
   screen_reset();

   send_command(DRIVER_OUTPUT_CONTROL);
   send_data((EPD_HEIGHT - 1) & 0xFF);
   send_data(((EPD_HEIGHT - 1) >> 8) & 0xFF);
   send_data(0x00);
   led_blink(5);

   send_command(BOOSTER_SOFT_START_CONTROL);
   send_data(0xD7);
   send_data(0xD6);
   send_data(0x9D);
   led_blink(5);

   send_command(WRITE_VCOM_REGISTER);
   send_data(0xA8);
   led_blink(5);

   send_command(SET_DUMMY_LINE_PERIOD);
   send_data(0x1A);
   led_blink(5);

   send_command(SET_GATE_TIME);
   send_data(0x08);
   led_blink(5);

   send_command(DATA_ENTRY_MODE_SETTING);
   send_data(0x03);
   led_blink(5);

   // Draw something

   // Sleep
   send_command(DEEP_SLEEP_MODE);
   led_blink(5);
   // wait_for_idle();
   // screen_reset();
   // led_blink_continuous();

   return 1;
}