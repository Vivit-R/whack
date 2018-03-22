#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "map.h"
#include "init.h"
#include "datastruct.h"


#define IFARG(s) (argc-1 && !(strcmp(argv[1], s)))

void leakstest();
void linkstest();

int main(int argc, char** argv) {
    if (IFARG("leaks")) {
        leakstest();
        printf("Checking for leaks...\n");
    }

    if (IFARG("links")) {
        printf("Checking links...\n");
        linkstest();
    }

    return 0;
}

void leakstest() {
    init_all();
    freeall();
}

void linkstest() {
    struct listlink *foo = malloc(sizeof (struct listlink));

    int *bar = malloc(sizeof (int));

    foo->prev = NULL;
    foo->next = NULL;

    addlink(foo, bar);
    addlink(foo, bar);
    addlink(foo, bar);

    clearlinks(foo, NULL);
    free(bar);
}

void mapstest() {
    dungeon = 
}

void displaytest() {
    init_display();

    /* TODO */

    end_display();
}
