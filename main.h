// Standard AVR includes
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
// #include <avr/eeprom.h>
#include <avr/pgmspace.h>
// #include <avr/sleep.h>
// #include <avr/wdt.h>
// #include <avr/power.h>

// Standard includes
#include <stdlib.h>

// These are optional, but nice to have around.
// Feel free to comment them out if you don't use them.
#ifdef DEBUG
#include "USART.h"
#endif

#include "macros.h"

// My stuff
#include "pinDefines.h"
#include "millis.h"
#include "led.h"
#include "node.h"
