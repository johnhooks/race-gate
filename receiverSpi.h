#ifndef RECEIVER_SPI_H
#define RECEIVER_SPI_H


#include <avr/io.h>
#include <util/delay.h>


#include "pinDefines.h"
#include "channels.h"


#define SLAVE_SELECT   SPI_SS_PORT &= ~(1 << SPI_SS)
#define SLAVE_DESELECT SPI_SS_PORT |= (1 << SPI_SS)


#define SPI_ADDRESS_SYNTH_A 0x01


void initSPI(void);
void setSynthRegisterB(uint32_t data);


#endif
