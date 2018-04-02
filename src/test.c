#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "item.h"
#include "map.h"
#include "command.h"
#include "monster.h"
#include "display.h"
#include "init.h"
#include "datastruct.h"
#include "you.h"

#define IFARG(s) (argc-1 && !(strcmp(argv[1], s)))

void linkstest();
void maptest();
void displaytest();
void testspecificmap(struct floor(*generate)(void));
void testhollow();
void testmon();
void testmove();

int main(int argc, char** argv) {
    initall();

    if (IFARG("leaks")) {
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
    } else if (IFARG("movement")) {
        testmove();
    } else {
        printf("Argument not recognized, or none was supplied!\n");
    }

    freeall();

    return 0;
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
    addlev(solidrock);
    addlev(solidrock);
    addlev(solidrock);
    addlev(solidrock);
}

void displaytest() {
    testspecificmap(bigroom);
}

void testspecificmap(struct floor(*generate)(void)) {
    addlev(generate);
    magicmapping(dungeon);
    refresh();
    getch();
}

void testhollow() {
    addlev(solidrock);
    hollowoutroom(dungeon, 10, 10, 10, 10);

    magicmapping(dungeon);
    refresh();
    getch();
}

void testmon() {
    addlev(bigroom);
    magicmapping(dungeon);
    spawnmons(3, mkmon('f', "dummy"), dungeon+curfloor);
    redraw();
    refresh();
    getch();
}

void testmove() {
    addlev(bigroom);
    inityou();
    putmon(randtile(TILE_FLOOR), &you);
    magicmapping(dungeon+curfloor);
    refresh();

    while (!done) {
        getcmd();
        refresh();
    }
}
