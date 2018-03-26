#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "item.h"
#include "map.h"
#include "display.h"
#include "init.h"
#include "datastruct.h"

#define IFARG(s) (argc-1 && !(strcmp(argv[1], s)))

void leakstest();
void linkstest();
void maptest();
void displaytest();
void testspecificmap(struct floor(*generate)(void));

int main(int argc, char** argv) {
    if (IFARG("leaks")) {
        leakstest();
        printf("Checking for leaks...\n");
    }

    if (IFARG("links")) {
        printf("Checking links...\n");
        linkstest();
    }

    if (IFARG("maps")) {
        printf("Checking maps...\n");
        maptest();
    }

    if (IFARG("display")) {
        displaytest();
    }

    if (IFARG("noise")) {
        testspecificmap(noise);
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
    addlev(solidRock);
    addlev(solidRock);
    addlev(solidRock);
    addlev(solidRock);
    freedungeon();
}

void displaytest() {
    testspecificmap(solidRock);
}

void testspecificmap(struct floor(*generate)(void)) {
    initdisplay();
    initdungeon();

    addlev(generate);
    magicmapping(dungeon);
    refresh();
    getch();

    freedungeon();
    enddisplay();
}
