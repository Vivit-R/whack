#ifndef __MAP__
#define __MAP__

#define UNDISCOVERED    -1   /* Tile has not yet been seen */
#define DISCOVERED       0   /* Tile is not in line of sight, but has been 
                                seen */
#define SEEN             1   /* Tile is in line of sight */

#define MAP_WIDTH 80
#define MAP_HEIGHT 26


#define NUM_TILE_TYPES 9

#define TILE_FLOOR          0
#define TILE_WALL           1
#define TILE_PILLAR         2
#define TILE_CLOSED_DOOR    3
#define TILE_OPEN_DOOR      4
#define TILE_ALTAR          5
#define TILE_UPSTAIR        6
#define TILE_DOWNSTAIR      7

#include "datastruct.h"
#include "item.h"

extern char tile_chars[NUM_TILE_TYPES];

/* Putting some forward-declarations of the structs before
 * including monster.h, because monster.h needs them. */
typedef struct t_tile tile;
#include "monster.h"

typedef struct t_tile {
    int ycoord;
    int xcoord;

    int seen; /* UNSEEN, SEEN, or VISIBLE? */
    int tiletype;
    char glyph;

    mon *occupant;
    item *item_pile;
} tile;

struct floor {
    int branch;
    struct room *rooms;
    tile grid[MAP_HEIGHT][MAP_WIDTH];
};

extern struct floor *dungeon;
extern int curfloor;
extern int dundepth;

struct floor solidrock();
struct floor noise();
struct floor bigroom();
struct floor threebythree();


void addlev(struct floor (*generate)(void));
void magicmapping(struct floor *l);
void hollowoutroom(struct floor *lev,
        int origy, int origx,
        int dimy, int dimx); 
void walledroom(struct floor *lev,
        int origy, int origx,
        int dimy, int dimx);

tile mktile(int ycoord, int xcoord, int tiletype);
tile *randtile(int tiletype);

#endif
