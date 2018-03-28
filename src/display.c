/* IN THE PROCESS OF SIMPLIFICATION */

#include <stdlib.h>
#include <ncurses.h>
#include "display.h"
#include "datastruct.h"

struct listlink *tiles_to_update;

void vupdtile(void *t);

/** MEMORY MANAGEMENT **/
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

/** STATE CHANGES **/
/* Determine what character to print to display a square */
char char_to_print(tile *t) {
    if (t->seen == UNDISCOVERED)
        return ' ';
    else if (t->occupant) /* TODO invisibles? */
        return t->occupant->glyph;
    else if (t->item_pile)
        return t->item_pile->glyph;
    else
        return t->glyph;

    /* Can't happen; dummy statement to satisfy compiler warning */
    return '\000';
}

/* Checks what tile to print at a specific location and prints it there */
void updtile(tile *t) {
   mvaddch(t->ycoord, t->xcoord, char_to_print(t));
}

void redraw() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            updtile(&(dungeon->grid[i][j]));
        }
    }
}


/** MESSAGE WINDOW FUNCTIONS **/
/* Displays an image with a single message, cleaning up after itself *
int wmessage(int nlines, int ncols, int begin_y, int begin_x const char *msg) {
    WINDOW *msgwin = newwin(nlines, ncols, begin_y, begin_x);
} */
