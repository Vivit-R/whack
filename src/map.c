/* FIXME: WHAT IF YOU CHANGE THE PROPERTIES OF A LEVEL THE PLAYER ISN'T ON? */
/* TODO MONSTER MOVEMENT */

#include <stdlib.h>
#include <ncurses.h>
#include "map.h"
#include "display.h"
#include "dice.h"

struct floor *dungeon;
int curfloor;
int dundepth;
char tile_chars[NUM_TILE_TYPES];

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
            if (!(rand() % 2)) ret.grid[i][j].tiletype = TILE_FLOOR;
        }
    }

    return ret;
}

struct floor bigroom() {
    struct floor ret = solidrock();
    hollowoutroom(&ret, 1, 1, MAP_HEIGHT-2, MAP_WIDTH-2);

    return ret;
}

/* Hollows out a room dimy rows high and dimx columns wide, with the upper-left
 * corner at row origy and column origx. */
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

    for (int i = origy; i < origy+dimy; i++) {
        for (int j = origx; j < origx+dimx; j++) {
            if (lev->grid[i][j].tiletype == TILE_WALL) {
                lev->grid[i][j].tiletype = TILE_FLOOR;
                lev->grid[i][j].glyph = tile_chars[TILE_FLOOR];
            }
        }
    }
}

/* Hollows out a room with a wall around it. */
void walledroom(struct floor *lev,
        int origy, int origx,
        int dimy, int dimx) {
    if (origx < 0 || origy < 0 || 
            origx > MAP_WIDTH || origy > MAP_HEIGHT ||
            dimy <= 2 || dimx < 2 ||
            origx + dimx > MAP_WIDTH || origy + dimy > MAP_HEIGHT) {
        // reporterror("Bad coordinates for hollowoutroom");
        return;
    }

    for (int i = origy; i < origy+dimy; i++) {
        if (i == origy || i == origy+dimy-1) {
            for (int j = origx; j < origx+dimx; j++) {
                if (lev->grid[i][j].tiletype == TILE_WALL) {
                    lev->grid[i][j].glyph = '-';
                }
            }
        } else {
            lev->grid[i][origx].glyph = '|';
            lev->grid[i][origx+dimx-1].glyph = '|';
        }
        magicmapping(lev);
        redraw();

    }
    hollowoutroom(lev, origy+1, origx+1, dimy-2, dimx-2);
    magicmapping(lev);
    redraw();

}


/* Classic 3x3 level a la the original rogue */ 
struct floor threebythree() {
    struct floor ret = solidrock();
    int numrooms = d(3, 3);

    int rooms[9] = {0};

    /* Randomly select some ninths of the map to make rooms in */
    for (int i = 0; i < numrooms; i++) {
        int r = rand() % 9;
        if (rooms[r]) {
            i--;
        } else {
            rooms[r] = 1;
        }
    }

    /* Make those rooms */
    for (int i = 0; i < 9; i++) {
        int sectory = i / 3;
        int sectorx = i % 3;

        /* NOTE: This math is reliant on the fact that
         * MAP_HEIGHT % 3 = MAP_WIDTH % 3 = 2 */
        if (rooms[i]) {
            int height = d(4, 2);
            int width = d(4, 6);
            int origy = ((MAP_HEIGHT / 3) * (sectory) +
                d(1, (MAP_HEIGHT / 3) - height));
            int origx = (MAP_WIDTH  / 3) * (sectorx) +
                d(1, (MAP_WIDTH  / 3) - width);

            if (origx < 1) {
                origx = 1;
            }

            if (origy < 1) {
                origy = 1;
            }

            walledroom(&ret, origy, origx, height, width);
        }
    }

    return ret;
} 



/** MEMORY MANAGEMENT **/
/* Adds a level to the dungeon */
void addlev(struct floor (*generate)(void)) {
    dungeon = realloc(dungeon, (1+dundepth) * sizeof (struct floor));
    dungeon[dundepth] = generate();
    dundepth++;
}

/* Initializes a tile */
tile mktile(int ycoord, int xcoord, int tiletype) {
    tile ret;
    ret.tiletype = tiletype;
    ret.glyph = tile_chars[tiletype];
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
tile *randtile(int tiletype) {
    tile *ret =
        &(dungeon[curfloor].grid[rand() % MAP_HEIGHT][rand() % MAP_WIDTH]);
    if (ret->tiletype == tiletype)
        return ret;
    return randtile(tiletype);
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

/* Allocates memory for the dungeon and initialize characters dungeon
 * features */
void initdungeon() {
    dungeon = malloc(sizeof (struct floor));
    curfloor = 0;


    for (int i = 0; i < NUM_TILE_TYPES; i++) {
        tile_chars[i] = ' ';
    }

    tile_chars[TILE_FLOOR]       = '.';
    tile_chars[TILE_WALL]        = '#';
    tile_chars[TILE_PILLAR]      = '0';
    tile_chars[TILE_CLOSED_DOOR] = '+';
    tile_chars[TILE_OPEN_DOOR]   = '\\';
    tile_chars[TILE_ALTAR]       = '_';
    tile_chars[TILE_UPSTAIR]     = '<';
    tile_chars[TILE_DOWNSTAIR]   = '>';
}

/* Frees the dungeon */
void freedungeon() {
    for (int i = dundepth-1; i >= 0; i--) {
        rmlev(&(dungeon[i]));
    }
    free(dungeon);
}


/** CHANGES TO STATE FOR ALREADY-GENERATED LEVELS **/
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
