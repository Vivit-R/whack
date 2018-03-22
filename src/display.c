#include <ncurses.h>
#include "display.h"
#include "datastruct.h"

void vupdate_tile(void *t);
void update_tile(tile *t);

/* Updates all tiles that need updating and pops them from the list. */
void update_tiles(struct listlink *l) {
    clearlinks(l, vupdate_tile);
}

/* Two seperate functions, update and vupdate, to allow passing of
 * function pointer to clearlinks */
void update_tile(tile *t) {
   mvaddch(t->ycoord, t->xcoord, char_to_print(t));
}

void vupdate_tile(void *t) {
    update_tile((tile*) t);
}

/* Determine what character to print to display a square */
char char_to_print(tile *t) {
    return t->item_pile ? t->item_pile->glyph : t->glyph;
}
