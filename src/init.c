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
