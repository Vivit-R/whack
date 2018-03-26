/* IN THE PROCESS OF SIMPLIFICATION */

#include <stdlib.h>
#include <ncurses.h>
#include "display.h"
#include "datastruct.h"

struct listlink *tiles_to_update;

void vupdtile(void *t);


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

/* Determine what character to print to display a square */
char char_to_print(tile *t) {
    if (t->seen == UNDISCOVERED) return ' ';
    else return t->item_pile ? t->item_pile->glyph : t->glyph;

    /* Can't happen; dummy statement to satisfy compiler warning */
    return '\000';
}

void updtile(tile *t) {
   mvaddch(t->ycoord, t->xcoord, char_to_print(t));
}
