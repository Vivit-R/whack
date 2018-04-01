#ifndef __MONSTER__
#define __MONSTER__

/* Putting some forward-declarations of the structs before
 * including map.h, because map.h needs them. */
typedef struct t_mon mon;
struct floor;
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
void spawnmons(int n, mon *m, struct floor *lev);
int movemon(int dy, int dx, mon *m);
#endif
