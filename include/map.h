#ifndef __MAP__
#define __MAP__

#define UNDISCOVERED    -1   /* Tile has not yet been seen */
#define DISCOVERED       0   /* Tile is not in line of sight, but has been 
                                seen */
#define SEEN             1   /* Tile is in line of sight */

#define MAP_WIDTH 80
#define MAP_HEIGHT 26

#define TILE_WALL           '#'
#define TILE_PILLAR         '|'
#define TILE_FLOOR          '.'
#define TILE_CLOSED_DOOR    '+'
#define TILE_OPEN_DOOR      '\\'
#define TILE_ALTAR          '_'
#define TILE_SWITCH_ON      ';'
#define TILE_SWITCH_OFF     ':'

#include "datastruct.h"
#include "item.h"

typedef struct type_tile {
    int ycoord;
    int xcoord;

    int seen; /* UNSEEN, SEEN, or VISIBLE? */
    char glyph;
    item *item_pile;
} tile;

struct floor {
    int branch;
    tile grid[MAP_HEIGHT][MAP_WIDTH];
};

extern struct floor *dungeon;
extern int dundepth;

struct floor solidRock();
struct floor noise();


void addlev(struct floor (*generate)(void));
void magicmapping(struct floor *l);
void hollowoutroom(struct floor *lev, int origy, int origx, int dimy,
        int dimx); 

#endif
