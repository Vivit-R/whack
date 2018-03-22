#include <ncurses.h>
#include "display.h"
#include "datastruct.h"

struct listlink *tiles_to_update;

void vupdtile(void *t);
void updtile(tile *t);

void init_display() {
    initscr();
    noecho();
}

void end_display() {
    echo();
    endwin();
}


/* Updates all tiles that need updating and pops them from the list. */
void updtiles(struct listlink *l) {
    clearlinks(l, vupdtile);
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

/* Sets a tile's visibility to */
void reveal_tile(tile *t) {
    return ;
}
