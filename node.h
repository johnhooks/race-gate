#ifndef NODE_H
#define NODE_H


#define NUM_NODES 5
#define NUM_READINGS 5
#define LAP_THRESHOLD 180


#include <avr/io.h>
#include "millis.h"
#include "receiver.h"
#include "USART.h"


struct node_t {
  uint16_t channelIndex;
  uint16_t readings[NUM_READINGS];
  uint8_t readIndex;
  uint16_t total;
  uint16_t average;
  uint32_t lastLap;
};


void initNodes(void);
void nodesUpdate();


#endif
