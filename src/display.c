#include <stdlib.h>
#include <ncurses.h>
#include "display.h"
#include "datastruct.h"

struct listlink *tiles_to_update;

void vupdtile(void *t);
void updtile(tile *t);


/* Sets up the curses display */
void initdisplay() {
    initscr();
    noecho();
    tiles_to_update = NULL;
}

/* Cleans up the curses display */
void enddisplay() {
    free(tiles_to_update);
    echo();
    endwin();
}


/* Updates all tiles that need updating and pops them from the list. */
void updtiles() {
    clearlinks(tiles_to_update, vupdtile);
    refresh();
}

/* Two seperate functions, update and vupdate, to allow passing of a
 * function pointer to clearlinks, which takes a (void*)(void*) */
void updtile(tile *t) {
   mvaddch(t->ycoord, t->xcoord, char_to_print(t));
}
void vupdtile(void *t) {
    updtile((tile*) t);
}

/* Determine what character to print to display a square */
char char_to_print(tile *t) {
    return t->item_pile ? t->item_pile->glyph : t->glyph;
}

/* Adds a tile to the list of tiles to update */
void queueupdt(tile *t) {
    tiles_to_update = addlink(tiles_to_update, t);
}
