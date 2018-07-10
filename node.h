#ifndef NODE_H
#define NODE_H


#include "led.h"


#define NUM_NODES 5
#define NUM_READINGS 5


typedef struct node_t {
  uint16_t channelIndex;
  color_t color;
  uint8_t readings[NUM_READINGS]; /* 8 bits per reading is enough */
  uint8_t readIndex;
  uint16_t total;
  uint8_t averageRssi;
  uint8_t peakRssi;
  uint32_t lapTimeout;
  uint8_t isGeneratingLap;
  uint8_t isActive;
  uint8_t genCount;
  uint8_t peakCount;
} node_t;


void initNodes(void);
void nodesUpdate();


#endif
