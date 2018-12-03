#include "main.h"


int main(void)
{
  millis_init();
  
  initADC();                    /* RSSI Reading */
  initSPI();                    /* RX5808 SPI */
  initLEDs();                   /* LED Strip PWM */
  initNodes();                  /* Virtual Receiver Nodes */

  #ifdef DEBUG
  initUSART();
  printString("DEBUG Enabled\n");
  #endif

  while (1) {
    nodesUpdate();
    if (rainbowing) {
      rainbow(100);
    }
  }
  return (0);
}
