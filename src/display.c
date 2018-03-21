#include <ncurses.h>
#include "display.h"

/* Updates all tiles that need updating and pops them from the list. */
void update_tiles(struct listlink *l) {
    if (l) {
        mvaddch(((tile*) l->elem)->ycoord,
                ((tile*) l->elem)->xcoord,
                char_to_print(l->elem));
    }
}

/* Determine what character to print to display a square */
char char_to_print(tile *t) {
    return t->item_pile ? t->item_pile->glyph : t->glyph;
}
