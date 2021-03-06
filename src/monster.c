#include <stdlib.h>
#include <string.h>
#include "monster.h"
#include "map.h"
#include "display.h"

mon *mregistry;
int nummons;

/** INITIALIZATION AND MEMORY MANAGEMENT **/
/* */
void initmons() {
    mregistry = malloc(sizeof (mon));
    nummons = 0;
}

/* Frees the data associated with all monsters, then frees mregistry. */
void freemons() {
    while (nummons > 0) {
        nummons--;
        rmmon(mregistry + nummons);
    }

    free(mregistry);
}

/* Initializes data for a monster and adds it to mregistry */
mon *mkmon(char glyph, const char *name) {
    mregistry = realloc(mregistry, (1+nummons) * (sizeof (mon)));
    mon *ret = mregistry+nummons;

    ret->glyph = glyph;
    ret->name = malloc((1+strlen(name)) * sizeof (char));
    ret->loc = NULL;

    strcpy(ret->name, name);
    nummons++;
    return ret;
}

/* Frees all data w/in a mon struct. Does not free struct itself; that will be
 * handled by freemons().
 * CHANGE THIS IF YOU CHANGE THE DEFINITION OF THE MON STRUCT. */
void rmmon(mon *m) {
    free(m->name);
}


/** CHANGES TO STATE **/
/* Attempts to place a monster at a given tile, returning an error code if
 * unsuccessful. */
int putmon(tile *dest, mon *m) {
    tile *prevloc = m->loc;
    if (!dest->occupant) {
        if (dest->tiletype != TILE_WALL) {
            dest->occupant = m;
            m->loc = dest;
            updtile(dest);
            if (prevloc) {
                prevloc->occupant = NULL;
                updtile(prevloc);
            }
            return 0;
        } else {
            return 1; /* Error code 1 = the tile was impassable */
        }
    } else {
        return 2; /* Error code 2 = the tile was occupied */
    }

    return -1; /* Can't happen */
}

/* Tries to put a monster in a location relative to its current one */
int movemon(int dy, int dx, mon *m) {
    int newy = m->loc->ycoord+dy;
    int newx = m->loc->xcoord+dx;

    if (newy < 0 || newy > MAP_HEIGHT || newx < 0 || newx > MAP_WIDTH) {
        return 1; /* Tile was out of bounds, and thus impassible */
    }

    return putmon(
            &((dungeon+curfloor)->grid[m->loc->ycoord+dy][m->loc->xcoord+dx]),
            m);
}

/* Spawns a number of copies of the given monster on the given level in random
   locations. Temporary, I hope hope hope.
   TODO integrate this with randtile? */
void spawnmons(int n, mon *m, struct floor *lev) {
    mon *cpy;
    int r1;
    int r2;
    cpy = mkmon(m->glyph, m->name);

    for (int i = 0; i < n; i++) {
        r1 = 1+(rand() % (MAP_HEIGHT-1));
        r2 = 1+(rand() % (MAP_WIDTH-1));
        while (putmon(&(lev->grid[r1][r2]), cpy));
    }
}
