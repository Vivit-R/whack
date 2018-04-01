#include <stdlib.h>
#include <time.h>
#include "command.h"
#include "item.h"
#include "init.h"

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
