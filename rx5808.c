#include "rx5808.h"


void initSPI(void)
{
  SPI_SS_DDR |= (1 << SPI_SS);  /* set SS output */
  SLAVE_DESELECT;               /* start not selected (high) */

  SPI_MOSI_DDR |= (1 << SPI_MOSI);  /* output on MOSI */
  SPI_MISO_PORT |= (1 << SPI_MISO); /* pullup on MISO */
  SPI_SCK_DDR |= (1 << SPI_SCK);    /* output on SCK */

  /* rx5808 usings default phase and polarity */
  SPCR |= (1 << SPR1);          /* div 64, safer for breadboards */
  SPCR |= (1 << MSTR);          /* clockmaster */
  SPCR |= (1 << SPE);           /* enable */
  SPCR |= (1 << DORD);          /* LSB first */
}

void SPI_tradeByte(uint8_t byte)
{
  SPDR = byte;                  /* SPI starts sending immediately */
  loop_until_bit_is_set(SPSR, SPIF); /* wait until done */
  /* SPDR now contains the received byte */
}

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
 *
 * NOTE: channelData does not require all 20 bits of data
 */
void SPI_setSynthRegisterB(uint8_t channelIndex)
{
  uint8_t byte;
  uint16_t channelData = getSynthRegisterB(channelIndex);

  SLAVE_SELECT;

  /**
   * The first byte has three parts to it; the register address, the
   * read/write bit, and the least 3 significant bits of the data.
   * We'll build that byte first, then ship it to the RF module.
   */

  /**
   * Part 1:
   * Set the 4 address bits starting at bit 0.
   */
  byte = (MODULE_ADDRESS_SYNTH_A & 0x0F);

  /**
   * Part 2:
   * To set the read/write bit, set a 1 to the 4th bit in the outboing byte.
   * We do this by shifting a 1 to the left to bit position 4, then use the
   * bitwise OR operation to set it to the outgoing byte without clearing
   * any other bits. */
  byte |= (1 << MODULE_RW);

  /**
   * Part 3:
   * Mask off all but the the least-significant 3 bits from the data with a
   * logic AND. The '0x07' is 0b00000111 in binary and Bitwise ANDing that
   * with the data will give us only those three bits that are set in the
   * data. Then shift those 3 bits to the left so they line up with bits 7
   * through 5 in the illustration in Figure 6.1 from the documentation. Use
   * the bitwise OR operation to set those three bits in the outgoing byte.
   */
  byte |= (channelData & 0x07) << 5;

  /**
   * Now that we've composed the first byte, ship it off.
   */
  SPI_tradeByte(byte);

  /**
   * Build a byte from the next 8 bits of the data, from bits [10 - 3] of the
   * data to be sent.
   */
  byte = (channelData >> 3) & 0xFF;

  SPI_tradeByte(byte);

  /**
   * Build the next byte from bits [18 - 11] of the data to be sent
   */
  byte = (channelData >> 11) & 0xFF;

  SPI_tradeByte(byte);

  /**
   * Set the final bit of the data, zeros for everything else.
   * Original
   *   byte = (channelData >> 19) & 0x01;
   */
  byte = 0;                     /* channelData would overflow */

  SPI_tradeByte(byte);

  /**
   * Finished!
   */
  SLAVE_DESELECT;
}
