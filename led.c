#include <avr/io.h>


#include "led.h"
#include "pinDefines.h"
#include "millis.h"


#define FIXPOINT 6
#define BRIGHTNESS 100
#define BRIGHTNESS_RATIO (BRIGHTNESS << FIXPOINT) / 255
#define DIM(X) ((X) * BRIGHTNESS_RATIO) >> FIXPOINT


uint8_t rainbowing = 1;


static uint8_t wheelPos = 0;
static uint32_t ledTimeout = 0;


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

uint8_t dim(uint8_t color, uint16_t brightness)
{
  return (color * brightness) >> 8;
}

void setStrip(color_t color)
{
  LED_PWM_R = dim(color.r, 50);
  LED_PWM_G = dim(color.g, 50);
  LED_PWM_B = dim(color.b, 50);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
color_t wheel(uint8_t wheelPos) {
  wheelPos = 255 - wheelPos;
  if (wheelPos < 85) {
    return (color_t) { 255 - wheelPos * 3, 0, 3 * wheelPos };
  }
  if (wheelPos < 170) {
    wheelPos -= 85;
    return (color_t) { 0, 3 * wheelPos, 255 - wheelPos * 3 };
  }
  wheelPos -= 170;
  return (color_t) { 3 * wheelPos, 255 - wheelPos * 3, 0 };
}

void rainbow(uint16_t wait)
{
  uint32_t now = millis_get();
  if (ledTimeout < now) {
    ledTimeout = now + wait;
    setStrip(wheel(wheelPos++));
  }
}
