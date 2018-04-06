#include <stdio.h>

#include "display.h"
#include "map.h"


void printlev(struct floor *l, FILE *stream) {
    fputc('\n', stream);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            fputc(char_to_print(&(l->grid[i][j])), stream); 
        }
        fputc('\n', stream);
    }
}

