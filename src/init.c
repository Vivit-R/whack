#include <stdlib.h>
#include <time.h>
#include "command.h"
#include "item.h"
#include "init.h"

char commands[128];

/* Initializes all commands to their default value. */
void initcommands() {
    for (int i = 0; i < 128; i++) {
        commands[i] = (char) i;
    }
}

/* initializes everything */
void initall() {
    srand(time(NULL));
    inititypes();
    initdisplay();
    initdungeon();
    initmons();
    initcommands();
}

/* frees everything */
void freeall() {
    freeitypes();
    freedungeon();
    enddisplay();
    freemons();
}
