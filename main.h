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

// My stuff
#include "macros.h"
#include "debug.h"
#include "pinDefines.h"
#include "millis.h"
#include "led.h"
#include "receiverSpi.h"
#include "receiver.h"
#include "node.h"
