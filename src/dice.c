#include <stdlib.h>
#include "dice.h"

/* Rolls (dice)D(sides) */
int d(int dice, int sides) {
    int ret = 0;

    if (dice > 0 && sides > 0) {
        for (int i = 0; i < dice; i++) {
            ret++;
            ret += rand() % sides;
        }
    }

    return ret;
}

/* Rolls 1d20 */
int d20() {
    return d(1, 20);
}
