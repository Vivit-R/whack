#ifndef __MONSTER__
#define __MONSTER__

/* Putting this forward-declaration of the typedef before
 * including map.h, because map.h needs it. */
typedef struct t_mon mon;
#include "map.h"

typedef struct t_mon {
    char *name;
    char glyph;
    tile *loc;
    
} mon;

extern mon *mregistry;
void rmmon(mon *m);
extern int nummons;

mon *mkmon(char glyph, const char *name);
#endif
