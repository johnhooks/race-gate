#include "led.h"


void initLEDs(void)
{
  LED_DDR |= (1 << LED_R) | (1 << LED_G) | (1 << LED_B);

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

void setStrip(uint8_t r, uint8_t g, uint8_t b)
{
  LED_PWM_R = r;
  LED_PWM_G = g;
  LED_PWM_B = b;
}
