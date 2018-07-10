#ifndef LED_H
#define LED_H


uint8_t rainbowing;


typedef struct color_t {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;


void initLEDs(void);
void setStrip(color_t color);
color_t wheel(uint8_t WheelPos);
void rainbow(uint16_t wait);


#endif
