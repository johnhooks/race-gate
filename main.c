#include "main.h"


/**
 * E2 5685 17
 * F2 5760 25
 * F4 5800 27
 * F7 5860 30
 * E6 5905 21
 */

int main(void)
{
  // clock_prescale_set(clock_div_1);                 /* CPU Clock: 8 MHz */

  initADC();                    /* RSSI Reading */
  initSPI();                    /* RX5808 SPI */
  initLEDs();                   /* LED Strip PWM */
  initUSART();

  printString("OK");

  setChannel(17);

  uint16_t rssi;

  while (1) {
    rssi = readRssi();
    printWord(rssi);
  }
  return (0);
}
