#include <stdlib.h>
#include "map.h"

struct floor *dungeon;
int dungeon_depth;

/* Creates a level filled with solid rock, from which we can then carve out
 * the actual labyrinth. */
struct floor solidRock() {
    struct floor ret;
    ret.branch = -1;

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            ret.grid[i][j].glyph = TILE_WALL;
            ret.grid[i][j].ycoord = i;
            ret.grid[i][j].xcoord = j;
            ret.grid[i][j].item_pile = NULL;
        }
    }

    return ret;
}

/* Adds a level to the dungeon */
void addlev(struct floor (*generate)(void)) {
    dungeon = realloc((1+dundepth) * malloc());
}

void freelev() {
    for (int i = 0; i < 
}

void init_dungeon() {
    dungeon = malloc(sizeof (struct floor));
}

void freedungeon() {
    for (int i = 0; i < dungeon_depth; i++) 
}
