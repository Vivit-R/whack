#include <stdlib.h>
#include <string.h>
#include "item.h"

void mkitype(char glyph, const char *idname, const char *unidname);
int rmitype();
void mkitem(struct itype itype, const char *name);

struct itype *itypes;
int num_itypes;

void init_itypes() {
    itypes = NULL;
    num_itypes = 0;

    mkitype('?', "dummy", "dummy");
}

void free_itypes() {
    while (rmitype());
}

void mkitype(char glyph, const char *idname, const char *unidname) {
    itypes = realloc(itypes, (1+num_itypes) * sizeof (struct itype));

    itypes[num_itypes].glyph = glyph;
    itypes[num_itypes].idname = malloc(sizeof (char) * (1+strlen(idname)));
    itypes[num_itypes].unidname = malloc(sizeof (char) * (1+strlen(unidname)));
    itypes[num_itypes].inscribe = NULL;

    strcpy(itypes[num_itypes].idname, idname);
    strcpy(itypes[num_itypes].unidname, unidname);

    num_itypes++;
}

/* Frees allocated data for the top itype */
int rmitype() {
    if (num_itypes) {
        num_itypes--;
        free(itypes[num_itypes].idname);
        free(itypes[num_itypes].unidname);
        free(itypes[num_itypes].inscribe);

        if (num_itypes)
            itypes = realloc(itypes, num_itypes * sizeof (struct itype));
        else
            free(itypes);
    }

    return num_itypes;
}


