#ifndef MILLIS_H
#define MILLIS_H


#include <avr/interrupt.h>
#include <util/atomic.h>


typedef uint32_t millis_t;


void millis_init(void);
millis_t millis_get(void);


#endif
