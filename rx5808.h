#ifndef RX5808_H
#define RX5808_H


#include <avr/io.h>
#include "pinDefines.h"
#include "channels.h"


#define SLAVE_SELECT   SPI_SS_PORT &= ~(1 << SPI_SS)
#define SLAVE_DESELECT SPI_SS_PORT |= (1 << SPI_SS)

#define MODULE_ADDRESS_SYNTH_A 0x01
#define MODULE_ADDRESS_POWER 0x0A

#define MODULE_RW 4

#define MIN_TUNE_TIME 30


void initSPI(void);

void SPI_tradeByte(uint8_t byte);

void SPI_setSynthRegisterB(uint8_t channelIndex);


#endif
