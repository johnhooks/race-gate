#ifndef RECEIVER_H
#define RECEIVER_H


#include "pinDefines.h"
#include "receiverSpi.h"
#include "millis.h"


#define MIN_TUNE_TIME 30


void initADC(void);
void setChannel(uint16_t channelIndex);
uint16_t readRssi(void);
uint8_t isReceiverReady(void);


#endif
