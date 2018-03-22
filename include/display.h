#ifndef __DISPLAY__
#define __DISPLAY__
#include "datastruct.h"
#include "map.h"

char char_to_print(tile *t);
void reveal_tile(tile *t);
extern struct listlink *tiles_to_update;

#endif
