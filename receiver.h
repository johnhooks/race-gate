#ifndef RECEIVER_H
#define RECEIVER_H


#include "pinDefines.h"
#include "receiverSpi.h"


#define MIN_TUNE_TIME 30


void initADC(void);
void setChannel(uint16_t channelIndex);
uint16_t readRssi(void);


#endif
