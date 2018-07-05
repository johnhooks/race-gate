#ifndef NODE_H
#define NODE_H


#define NUM_NODES 5
#define NUM_READINGS 5


#include <avr/io.h>
#include "node.h"


struct node {
  uint16_t channelIndex;
  uint8_t readings[NUM_READINGS];
  uint8_t readIndex;
  uint16_t total;
  uint8_t average;
};

extern struct node nodes[];


void initNodes(void);


#endif
