#ifndef __DISPLAY__
#define __DISPLAY__
#include "datastruct.h"
#include "map.h"

char char_to_print(tile *t);
extern struct listlink *tiles_to_update;
void updtiles();
void queueupdt(tile *t);

#endif
