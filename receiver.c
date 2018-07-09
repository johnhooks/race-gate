#include "receiver.h"


uint32_t receiverTimeout;


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
  receiverTimeout = millis_get() + MIN_TUNE_TIME;
}

uint16_t readRssi(void)
{
  ADCSRA |= (1 << ADSC);                 /* start ADC conversion */
  loop_until_bit_is_clear(ADCSRA, ADSC); /* wait until done */
  return ADC;                            /* read ADC input */
}

uint8_t isReceiverReady(void)
{
  return receiverTimeout < millis_get();
}
