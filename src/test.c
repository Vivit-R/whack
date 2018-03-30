#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "item.h"
#include "map.h"
#include "monster.h"
#include "display.h"
#include "init.h"
#include "datastruct.h"

#define IFARG(s) (argc-1 && !(strcmp(argv[1], s)))

void leakstest();
void linkstest();
void maptest();
void displaytest();
void testspecificmap(struct floor(*generate)(void));
void testhollow();
void testmon();

int main(int argc, char** argv) {
    if (IFARG("leaks")) {
        leakstest();
        printf("Checking for leaks...\n");
    } else if (IFARG("links")) {
        printf("Checking links...\n");
        linkstest();
    } else if (IFARG("maps")) {
        printf("Checking maps...\n");
        maptest();
    } else if (IFARG("monsters")) {
        printf("Checking monsters...\n");
        testmon();
    } else if (IFARG("display")) {
        displaytest();
    } else if (IFARG("noise")) {
        testspecificmap(noise);
    } else if (IFARG("hollow")) {
        testhollow();
    } else if (IFARG("monsters")) {
        testmon();
    } else {
        printf("Argument not recognized, or none was supplied!\n");
    }

    return 0;
}


/* Test functions */
void leakstest() {
    initall();
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

void maptest() {
    initdungeon();
    addlev(solidrock);
    addlev(solidrock);
    addlev(solidrock);
    addlev(solidrock);
    freedungeon();
}

void displaytest() {
    testspecificmap(bigroom);
}

void testspecificmap(struct floor(*generate)(void)) {
    initall();

    addlev(generate);
    magicmapping(dungeon);
    refresh();
    getch();

    freeall();
}

void testhollow() {
    initall();

    addlev(solidrock);

    hollowoutroom(dungeon, 10, 10, 10, 10);

    magicmapping(dungeon);
    refresh();
    getch();

    freeall();
}

void testmon() {
    initall();

    addlev(bigroom);
    magicmapping(dungeon);
    spawnmons(3, mkmon('f', "dummy"), dungeon+curfloor);
    redraw();
    refresh();
    getch();

    freeall();
}
