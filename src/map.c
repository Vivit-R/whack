/* FIXME: WHAT IF YOU CHANGE THE PROPERTIES OF A LEVEL THE PLAYER ISN'T ON? */
/* TODO MONSTER MOVEMENT */

#include <stdlib.h>
#include "map.h"
#include "display.h"

struct floor *dungeon;
int curfloor;
int dundepth;

void rmlev(struct floor *lev);
void setseen(tile *t, int seen);
void seetile(tile *t);
void discovertile(tile *t);
void forgettile(tile *t);

/** LEVEL GENERATION **/
/* Creates and returns a level filled with solid rock, from which we can then 
 * carve out the actual labyrinth. */
struct floor solidrock() {
    struct floor ret;
    ret.branch = -1;

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            ret.grid[i][j] = mktile(i, j, TILE_WALL);
        }
    }

    return ret;
}

/* Generates a level where every square has a 50/50 chance of being a wall
 * and a 50/50 chance of being a floor. */
struct floor noise() {
    struct floor ret = solidrock();

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (!(rand() % 2)) ret.grid[i][j].glyph = TILE_FLOOR;
        }
    }
    return ret;
}

struct floor bigroom() {
    struct floor ret = solidrock();
    hollowoutroom(&ret, 1, 1, MAP_HEIGHT-2, MAP_WIDTH-2);

    return ret;
}


void hollowoutroom(struct floor *lev,
        int origy, int origx,
        int dimy, int dimx) {
    if (origx < 0 || origy < 0 || 
            origx > MAP_WIDTH || origy > MAP_HEIGHT ||
            dimy < 0 || dimx < 0 ||
            origx + dimx > MAP_WIDTH || origy + dimy > MAP_HEIGHT) {
        // reporterror("Bad coordinates for hollowoutroom");
        return;
    }

    for (int i = 0; i < dimy; i++) {
        for (int j = 0; j < dimx; j++) {
            if (lev->grid[origy+i][origx+j].glyph == TILE_WALL)
                lev->grid[origy+i][origx+j].glyph = TILE_FLOOR;
        }
    }
}


/* Classic 3x3 level a la the original rogue *
struct floor nineRooms() {
    struct floor ret = solidrock();
    
    for 
} */




/** MEMORY MANAGEMENT **/
/* Adds a level to the dungeon */
void addlev(struct floor (*generate)(void)) {
    dungeon = realloc(dungeon, (1+dundepth) * sizeof (struct floor));
    dungeon[dundepth] = generate();
    dundepth++;
}

/* Initializes a tile */
tile mktile(int ycoord, int xcoord, char glyph) {
    tile ret;
    ret.glyph = glyph;
    ret.ycoord = ycoord;
    ret.xcoord = xcoord;
    ret.seen = UNDISCOVERED;
    ret.item_pile = NULL;
    ret.occupant = NULL;

    return ret;
}

/* Randomly selects a tile with the given glyph 
 * TODO make this more flexible than just a single glyph
 * also what if there is no such tile on the board? */
tile *randtile(char glyph) {
    tile *ret =
        &(dungeon[curfloor].grid[rand() % MAP_HEIGHT][rand() % MAP_WIDTH]);
    if (ret->glyph == glyph)
        return ret;
    return randtile(glyph);
}

/* Removes given floor from the dungeon */
/* CHANGEME IF YOU ADD POINTERS TO THE TILE STRUCT */
void rmlev(struct floor *lev) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            free(lev->grid[i][j].item_pile);
        }
    }
}

/* Allocates memory for the dungeon */
void initdungeon() {
    dungeon = malloc(sizeof (struct floor));
    curfloor = 0;
}

/* Frees the dungeon */
void freedungeon() {
    for (int i = dundepth-1; i >= 0; i--) {
        rmlev(&(dungeon[i]));
    }
    free(dungeon);
}


/** CHANGES TO STATE **/
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
    updtile(t);
}

void seetile(tile *t) { setseen(t, SEEN); }
void discovertile(tile *t) { setseen(t, DISCOVERED); }
void forgettile(tile *t) { setseen(t, UNDISCOVERED); }
