#include <stdio.h>

#include "display.h"
#include "map.h"

void printlev(struct floor *l) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            putchar(char_to_print(&(l->grid[i][j]))); 
        }
        printf("\n\r");
    }
}

