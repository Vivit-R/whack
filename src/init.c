#include "command.h"
#include "item.h"
#include "init.h"

char commands[128];

/* Initializes all commands to their default value. */
void init_commands() {
    for (int i = 0; i < 128; i++) {
        commands[i] = (char) i;
    }
}

void init_all() {
    init_itypes();
    init_commands();
}

void free_all() {
    free_itypes();
}
