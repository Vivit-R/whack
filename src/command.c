#include <ncurses.h>

#include "command.h"
#include "you.h"

extern int done;

char commands[128];
int dircmd[128][2];

/* Initializes all commands to their default value. */
void initcommands() {
    for (int i = 0; i < 128; i++) {
        commands[i] = (char) i;
    }

    for (int i = 0; i < 128; i++) {
        dircmd[i][0] = 0;
        dircmd[i][1] = 0;
    }

    dircmd['h'][0] =  0; dircmd['h'][1] = -1;
    dircmd['j'][0] =  1; dircmd['j'][1] =  0;
    dircmd['k'][0] = -1; dircmd['k'][1] =  0;
    dircmd['l'][0] =  0; dircmd['l'][1] =  1;
    dircmd['y'][0] = -1; dircmd['y'][1] = -1;
    dircmd['u'][0] = -1; dircmd['u'][1] =  1;
    dircmd['b'][0] =  1; dircmd['b'][1] = -1;
    dircmd['n'][0] =  1; dircmd['n'][1] =  1;
}

/* Getches a keystroke, translates it into a command via the commands[] array,
   and then executes the appropriate command. */
void getcmd() {
    char cmd = commands[(int) getch()];

    switch (cmd) {
        case 'h':
        case 'j':
        case 'k':
        case 'l':
        case 'y':
        case 'u':
        case 'b':
        case 'n':
            moveyou(cmd);
            break;

        case 'q':
            done = 1;
            break;

        default:
            break;
    }
}
