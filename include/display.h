#ifndef __DISPLAY__
#define __DISPLAY__
#include "datastruct.h"
#include "map.h"

#define FRAMECHAR '*'

char char_to_print(tile *t);
void updtile(tile *t);
void redraw();

#endif
