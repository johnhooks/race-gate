#ifndef LED_H
#define LED_H


#include <avr/io.h>
#include "pinDefines.h"


void initLEDs(void);
void setStrip(uint8_t r, uint8_t g, uint8_t b);


#endif
