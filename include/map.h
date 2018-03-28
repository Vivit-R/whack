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

/* Putting some forward-declarations of the structs before
 * including monster.h, because monster.h needs them. */
typedef struct t_tile tile;
#include "monster.h"

typedef struct t_tile {
    int ycoord;
    int xcoord;

    int seen; /* UNSEEN, SEEN, or VISIBLE? */
    char glyph;

    mon *occupant;
    item *item_pile;
} tile;

struct floor {
    int branch;
    tile grid[MAP_HEIGHT][MAP_WIDTH];
};

extern struct floor *dungeon;
extern struct floor *curfloor;
extern int dundepth;

struct floor solidrock();
struct floor noise();
struct floor bigroom();


void addlev(struct floor (*generate)(void));
void magicmapping(struct floor *l);
void hollowoutroom(struct floor *lev, int origy, int origx, int dimy,
        int dimx); 

tile mktile(int ycoord, int xcoord, char glyph);

#endif
