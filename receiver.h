#ifndef RECEIVER_H
#define RECEIVER_H


#include <stdint.h>


void initADC(void);
void setChannel(uint16_t channelIndex);
uint16_t readRssi(void);
uint8_t isReceiverReady(void);


#endif
