#ifndef CHANNELS_H
#define CHANNELS_H


#include <avr/pgmspace.h>

#include "channels.h"


extern const uint16_t channelTable[];

extern const uint16_t channelFreqTable[];

uint16_t getSynthRegisterB(uint8_t index);
uint16_t getFrequency(uint8_t index);


#endif