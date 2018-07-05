#include "receiver.h"


void initADC(void)
{
  /* MUX[3:0] 0000 for ADC0 */
  ADMUX |= (1 << REFS0);                 /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0); /* ADC clock prescaler 8 */
  ADCSRA |= (1 << ADEN);                 /* enable ADC */
}

void setChannel(uint16_t channelIndex)
{
  uint32_t channelData = getSynthRegisterB(channelIndex);
  setSynthRegisterB(channelData);
}

uint16_t readRssi(void)
{
  uint16_t rssiReading;
  ADCSRA |= (1 << ADSC);                 /* start ADC conversion */
  loop_until_bit_is_clear(ADCSRA, ADSC); /* wait until done */
  rssiReading = ADC;                     /* read ADC input */
  return rssiReading;
}
