#include "main.h"


/**
 * E2 5685 17
 * F2 5760 25
 * F4 5800 27
 * F7 5860 30
 * E6 5905 21
 */

static inline void initTimers(void)
{
  /* Timer 0 A, B */
  TCCR0A |= (1 << WGM00);       /* Fast PWM mode, 8-bit */
  TCCR0A |= (1 << WGM01);       /* Fast PWM mode, pt.2 */
  TCCR0B |= (1 << CS01);        /* PWM Freq = F_CPU/8/256 */
  TCCR0A |= (1 << COM0A1);      /* PWM output on OCR0A */
  TCCR0A |= (1 << COM0B1);      /* PWM output on OCR0B */

  /* Timer 2 A */
  TCCR2A |= (1 << WGM20);       /* Fast PWM mode, 8-bit */
  TCCR2A |= (1 << WGM21);       /* Fast PWM mode, pt.2 */
  TCCR2B |= (1 << CS21);        /* PWM Freq = F_CPU/8/256  */
  TCCR2A |= (1 << COM2B1);      /* PWM output on OCR2B */
}

static inline void initADC0(void)
{
  /* MUX[3:0] 0000 for ADC0 */
  ADMUX |= (1 << REFS0);                 /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0); /* ADC clock prescaler 8 */
  ADCSRA |= (1 << ADEN);                 /* enable ADC */
}

uint16_t readRssi(void)
{
  uint16_t rssiReading;
  ADCSRA |= (1 << ADSC);                 /* start ADC conversion */
  loop_until_bit_is_clear(ADCSRA, ADSC); /* wait until done */
  rssiReading = ADC;                     /* read ADC input */
  return rssiReading;
}

void setRGB(uint8_t R, uint8_t G, uint8_t B)
{
  OCR0B = R;
  OCR2B = G;
  OCR0A = B;
}

int main(void)
{
  LED_DDR |= (1 << LED_R);
  LED_DDR |= (1 << LED_G);
  LED_DDR |= (1 << LED_B);

  initADC0();
  initTimers();
  initSPI();

  // clock_prescale_set(clock_div_1);                 /* CPU Clock: 8 MHz */
  initUSART();
  // printString("OK");

  while (1) {



  }
  return (0);
}
