
/* FIXME: WHAT IF YOU CHANGE THE PROPERTIES OF A LEVEL THE PLAYER ISN'T ON? */

#include <stdlib.h>
#include "map.h"
#include "display.h"

struct floor *dungeon;
int dundepth;

void rmlev(struct floor lev);
void setseen(tile *t, int seen);
void seetile(tile *t);
void discovertile(tile *t);
void forgettile(tile *t);

/* Creates and returns a level filled with solid rock, from which we can then 
 * carve out the actual labyrinth. */
struct floor solidRock() {
    struct floor ret;
    ret.branch = -1;

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            ret.grid[i][j].glyph = TILE_WALL;
            ret.grid[i][j].ycoord = i;
            ret.grid[i][j].xcoord = j;
            ret.grid[i][j].seen = -1;
            ret.grid[i][j].item_pile = NULL;
        }
    }

    return ret;
}

/* Adds a level to the dungeon */
void addlev(struct floor (*generate)(void)) {
    dungeon = realloc(dungeon, (1+dundepth) * sizeof (struct floor));
    dungeon[dundepth] = generate();
    dundepth++;
}

/* Removes given floor from the dungeon */
/* CHANGEME IF YOU ADD POINTERS TO THE TILE STRUCT */
void rmlev(struct floor lev) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            free(lev.grid[i][j].item_pile);
        }
    }
}

/* Initializes the dungeon */
void initdungeon() {
    dungeon = malloc(sizeof (struct floor));
}

/* Frees the dungeon */
void freedungeon() {
    for (int i = dundepth-1; i >= 0; i--) {
        rmlev(dungeon[i]);
    }
    free(dungeon);
}

/* Sets all tiles on the given level to visible */
void magicmapping(struct floor *lev) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            discovertile(&(lev->grid[i][j]));
        }
    }
}

/* Sets a tile's visibility */
void setseen(tile *t, int seen) {
    t->seen = seen;
    queueupdt(t);
}

void seetile(tile *t) { setseen(t, SEEN); }
void discovertile(tile *t) { setseen(t, DISCOVERED); }
void forgettile(tile *t) { setseen(t, UNDISCOVERED); }
