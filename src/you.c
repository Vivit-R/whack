#include <string.h>
#include <stdlib.h>

#include "command.h"
#include "monster.h"
#include "map.h"
#include "you.h"

mon you;

void inityou() {
    you.name = malloc(sizeof (char) * (strlen("You") + 1));
    strcpy(you.name, "You");

    you.glyph = '@';

}

void freeyou() {
    free(you.name);
}

void moveyou(char input) {
    movemon(dircmd[(int) input][0], dircmd[(int) input][1], &you);
}
