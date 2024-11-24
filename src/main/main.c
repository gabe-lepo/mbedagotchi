#include "../spi/spi.h"
#include "../led/led.h"
#include "../uart/uart.h"

// LED controls
#define ON 1
#define OFF 0

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
   print_uart("# UART initialization done");

   // SPI setup
   print_uart("# Starting SPI setup...");
   spi_setup();
   print_uart("# SPI setup done");

   // Screen setup
   screen_reset();
   print_uart("# Screen reset done");
   send_command(DRIVER_OUTPUT_CONTROL);
   print_uart("# Send command done");
   send_data((EPD_HEIGHT - 1) & 0xFF);
   print_uart("# Send data done");
   send_data(((EPD_HEIGHT - 1) >> 8) & 0xFF);
   print_uart("# Send data done");
   send_data(0x00);
   print_uart("# Send data done");
   send_command(BOOSTER_SOFT_START_CONTROL);
   print_uart("# Send command done");
   send_data(0xD7);
   print_uart("# Send data done");
   send_data(0xD6);
   print_uart("# Send data done");
   send_data(0x9D);
   print_uart("# Send data done");
   send_command(WRITE_VCOM_REGISTER);
   print_uart("# Send command done");
   send_data(0xA8);
   print_uart("# Send data done");
   send_command(SET_DUMMY_LINE_PERIOD);
   print_uart("# Send command done");
   send_data(0x1A);
   print_uart("# Send data done");
   send_command(SET_GATE_TIME);
   print_uart("# Send command done");
   send_data(0x08);
   print_uart("# Send data done");
   send_command(DATA_ENTRY_MODE_SETTING);
   print_uart("# Send command done");
   send_data(0x03);
   print_uart("# Send data done");

   // Draw something

   // Sleep
   send_command(DEEP_SLEEP_MODE);
   print_uart("# Send command done");
   wait_for_idle();
   print_uart("# Done waiting for idle");
   screen_reset();
   print_uart("# Screen reset done");

   // LED
   print_uart("# Blinking LED continuously");
   led_blink_continuous();

   return 1;
}