#include <avr/io.h>
#include <util/delay.h>


#include "pinDefines.h"
#include "channels.h"
#include "receiverSpi.h"


#define SLAVE_SELECT   SPI_SS_PORT &= ~(1 << SPI_SS)
#define SLAVE_DESELECT SPI_SS_PORT |= (1 << SPI_SS)


#define SPI_ADDRESS_SYNTH_A 0x01


/**
 * Format is LSB first, with the following bits in order:
 *     4 bits - address
 *     1 bit  - read/write enable
 *    20 bits - data
 *
 * Address for frequency select (Synth Register B) is 0x1
 * Expected data is (LSB):
 *     7 bits - A counter divider ratio
 *      1 bit - seperator
 *    12 bits - N counter divder ratio
 *
 * Forumla for calculating N and A is:/
 *    F_lo = 2 * (N * 32 + A) * (F_osc / R)
 *    where:
 *        F_osc = 8 Mhz
 *        R = 8
 *
 * Refer to RTC6715 datasheet for further details.
 */


static inline void slaveSelect(void);
static inline void slaveDeselect(void);
static inline void clockHigh(void);
static inline void clockLow(void);
static inline void sendBit(uint8_t value);
static inline void sendBits(uint32_t bits, uint8_t count);
static inline void sendRegister(uint8_t address, uint32_t data);


void initSPI(void)
{
  SPI_SS_DDR |= (1 << SPI_SS);      /* set SS output */
  SLAVE_DESELECT;                   /* start not selected (high) */
  SPI_DATA_DDR |= (1 << SPI_DATA);  /* output on DATA */
  SPI_DATA_PORT |= (1 << SPI_DATA); /* pullup on DATA  */
  SPI_CLK_DDR |= (1 << SPI_CLK);    /* output on CLK */
}

/**
 * Set SynthRegisterB to channel at channelIndex of the channelTable.
 */
void setSynthRegisterB(uint32_t data)
{
  sendRegister(SPI_ADDRESS_SYNTH_A, data);
}


/**
 * Intend on getting SPI hardware to work, but for now just bit bang.
 */
static inline void sendRegister(uint8_t address, uint32_t data)
{
  slaveSelect();
  sendBits(address, 4);
  sendBit(1);                   /* enable write */
  sendBits(data, 20);
  slaveDeselect();
};

static inline void sendBits(uint32_t bits, uint8_t count)
{
  for (uint8_t i = 0; i < count; i++) {
    sendBit(bits & 0x1);
    bits >>= 1;
  }
}

static inline void sendBit(uint8_t value)
{
  clockLow();

  if (value & 0x1) {
    SPI_DATA_PORT |= (1 << SPI_DATA);  /* 1 */
  } else {
    SPI_DATA_PORT &= ~(1 << SPI_DATA); /* 0 */
  }
  _delay_us(1);

  clockHigh();
  clockLow();
}

static inline void slaveSelect(void)
{
  SLAVE_SELECT;
  _delay_us(1);
}

static inline void slaveDeselect(void)
{
  SLAVE_DESELECT;
  _delay_us(1);
}

static inline void clockHigh(void)
{
  SPI_CLK_PORT |= (1 << SPI_CLK);
  _delay_us(1);
}

static inline void clockLow(void)
{
  SPI_CLK_PORT &= ~(1 << SPI_CLK);
  _delay_us(1);
}
