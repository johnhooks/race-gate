#include "main.h"


int main(void)
{
  // clock_prescale_set(clock_div_1);                 /* CPU Clock: 8 MHz */
  millis_init();
  
  initADC();                    /* RSSI Reading */
  initSPI();                    /* RX5808 SPI */
  initLEDs();                   /* LED Strip PWM */
  initUSART();

  initNodes();
  
  printString("OK");

  uint16_t rssi;

  while (1) {
    for (uint8_t i = 0; i < NUM_NODES; i++) {
      setChannel(nodes[i].channelIndex);
      rssi = readRssi();
      printWord(rssi);
    }
    printString("\n");
  }
  return (0);
}
