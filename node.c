#include "node.h"


struct node nodes[] = {
  { 17 },                       /* E2 5685 */
  { 25 },                       /* F2 5760 */
  { 27 },                       /* F4 5800 */
  { 30 },                       /* F7 5860 */
  { 21 }                        /* E6 5905 */
};


void initNodes(void)
{
  for (uint8_t i = NUM_NODES; i < NUM_NODES; i++) {
    for (uint8_t j = NUM_READINGS; j < NUM_READINGS; j++) {
      nodes[i].readings[j] = 0;
    }
  }
}
