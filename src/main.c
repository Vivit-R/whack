#include <stdlib.h>
#include <time.h>
#include "command.h"
#include "you.h"
#include "item.h"
#include "init.h"

int done;

/* initializes everything */
void initall() {
    srand(time(NULL));
    inititypes();
    initdisplay();
    initdungeon();
    initmons();
    initcommands();
    inityou();
}

/* frees everything */
void freeall() {
    freeitypes();
    freedungeon();
    enddisplay();
    freemons();
    freeyou();
}
