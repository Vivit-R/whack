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

void initall() {
    inititypes();
    initdisplay();
    initcommands();
}

void freeall() {
    freeitypes();
    enddisplay();
}
