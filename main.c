#define DEBUG


#include "main.h"


int main(void)
{
  // clock_prescale_set(clock_div_1);                 /* CPU Clock: 8 MHz */
  millis_init();
  
  initADC();                    /* RSSI Reading */
  initSPI();                    /* RX5808 SPI */
  initLEDs();                   /* LED Strip PWM */

  initNodes();                  /* Zero out readings arrays */

  #ifdef DEBUG
  initUSART();
  printString("DEBUG ENABLED");
  #endif

  while (1) {
    setStrip(255, 75, 5);
    nodesUpdate();
  }
  return (0);
}
