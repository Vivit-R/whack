#ifndef __MAP__
#define __MAP__

#define UNSEEN -1   /* Tile has not yet been seen */
#define SEEN    0   /* Tile is not in line of sight, but has been seen */
#define VISIBLE 1   /* Tile is in line of sight */

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
extern int dungeon_depth;

#endif
