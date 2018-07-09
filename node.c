#include "node.h"


static enum statuses { init, tuning } status;


static struct node_t nodes[] = {
  { 17 },                       /* E2 5685 */
  { 25 },                       /* F2 5760 */
  { 27 },                       /* F4 5800 */
  { 30 },                       /* F7 5860 */
  { 21 }                        /* E6 5905 */
};


static struct node_t *node;


static uint16_t rawRssi;
static uint8_t nodeIndex = 0;


static void nodeFilterRssi()
{
  node->total -= node->readings[node->readIndex]; /* Remove oldest reading */
  node->total += rawRssi;       /* Add new reading to the total */
  node->readings[node->readIndex] = rawRssi; /* Push new reading into array */
  node->readIndex++;                         /* Advance the index */
  if (node->readIndex >= NUM_READINGS) node->readIndex = 0; /* Loop around */
  node->average = node->total / NUM_READINGS; /* Calculate the average */
}

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
  if (status == init) {
    node = &nodes[nodeIndex];
    setChannel(node->channelIndex);
    status = tuning;
  } else if (status == tuning && isReceiverReady()) {
    rawRssi = readRssi();
    nodeFilterRssi();
    status = init;
    nodeIndex++;
    if (nodeIndex >= NUM_NODES) {
      nodeIndex = 0;
      /* A full set of reads just completed */
      for (uint8_t i = 0; i < NUM_NODES; i++) {
        printWord(nodes[i].average);
      }
      printString("\n");
    }
  }
}
