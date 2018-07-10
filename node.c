#include <avr/io.h>
#include "millis.h"
#include "receiver.h"
#include "led.h"
#include "debug.h"
#include "node.h"


#define RSSI_THRESHOLD 215
#define LAP_MIN_TIME 3000       /* milliseconds */


static enum statuses { init, tune, next } status;


static node_t nodes[] = {
  { 17, {.r = 255} },             /* E2 5685, Red */
  { 25, {.b = 255} },             /* F2 5760, Blue */
  { 27, {.g = 255, .r = 255 } },             /* F4 5800, Yellow */
  { 30, {.g = 255} },             /* F7 5860, Green */
  { 21, {.r = 255, .b = 255 } }              /* E6 5905, Purple */
};


static node_t *node;


static uint32_t now;            /* Set before reading the group of nodes. */
static uint16_t rawRssi;
static uint8_t nodeIndex = 0;


static void update(void);       /* Update selected node */
static void readFilteredRssi(void);
static inline void incNodeIndex(void);
static inline uint8_t nodeIsActive(void);


void initNodes(void)
{
  status = init;
  for (uint8_t i = NUM_NODES; i < NUM_NODES; i++) {
    for (uint8_t j = NUM_READINGS; j < NUM_READINGS; j++) {
      nodes[i].readings[j] = 0;
    }
  }
}

void nodesUpdate(void)
{
  switch (status) {
  case init:
    now = millis_get();
    status = next;
#ifdef DEBUG
    for (uint8_t i = 0; i < NUM_NODES; i++) {
      printWord(nodes[i].averageRssi);
    }
    printString("\n");
#endif
    break;
  case next:
    node = &nodes[nodeIndex];
    setChannel(node->channelIndex);
    status = tune;
    break;
  case tune:
    if (isReceiverReady()) {
      update();
      incNodeIndex();
      status = nodeIndex == 0 ? init : next;
    }
    break;
  }
}


static void readFilteredRssi(void)
{
  rawRssi = readRssi();
  node->total -= node->readings[node->readIndex]; /* Remove oldest reading */
  node->total += rawRssi;       /* Add new reading to the total */
  node->readings[node->readIndex] = rawRssi; /* Push new reading into array */
  node->readIndex++;                         /* Advance the index */
  if (node->readIndex >= NUM_READINGS) node->readIndex = 0; /* Loop around */
  node->averageRssi = node->total / NUM_READINGS; /* Calculate the average */
}

/**
 * Update the current node.
 */
static void update(void)
{
  readFilteredRssi();
  if (node->isGeneratingLap) {
    if (node->averageRssi < RSSI_THRESHOLD) {
      if (node->genCount < 3) { /* Remove quick spikes. */
        node->isGeneratingLap = 0;
        return;
      } else {
        node->lapTimeout = now + LAP_MIN_TIME;
        node->isGeneratingLap = 0;
#ifdef DEBUG
        printString("LAP!\n");
#endif
        setStrip(node->color);
        rainbowing = 0;
        return;
      }
    }
    node->genCount++;
  } else if (node->lapTimeout < now && node->averageRssi >= RSSI_THRESHOLD) {
    node->genCount = 0;
    node->isGeneratingLap = 1;
  }
}

/**
 * Increment the nodeIndex or reset it to 0.
 */
static inline void incNodeIndex(void)
{
  if (++nodeIndex >= NUM_NODES) nodeIndex = 0;
}

/**
 * Return bool of whether or not the current node is active.  If the
 * isActive flag is not set, it checks if the lapTimeout has lapsed
 * and sets the isActive flag accordingly.
 */
static inline uint8_t nodeIsActive(void)
{
  return node->isActive || (node->isActive = node->lapTimeout < now);
}
