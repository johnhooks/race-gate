#include <avr/interrupt.h>
#include <util/atomic.h>
#include "millis.h"


static volatile millis_t milliseconds = 0; /* 49.71 Days of milliseconds */


void millis_init()
{
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS10); /* CTC Mode, No prescaling */
  TIMSK1 = (1 << OCIE1A); /* Output Compare A Match Interrupt Enable */
  OCR1A = F_CPU /  1000;
  sei();
}

millis_t millis_get()
{
  millis_t ms;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    ms = milliseconds;
  }
  return ms;
}

ISR(TIMER1_COMPA_vect)
{
  ++milliseconds;
}
