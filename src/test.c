#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "init.h"
#include "datastruct.h"


void test_leaks();
void test_links();

int main(int argc, char** argv) {
    if (argc-1 && !(strcmp(argv[1], "leak"))) {
        test_leaks();
        printf("Checking for leaks...\n");
    }

    if (argc-1 && !(strcmp(argv[1], "links"))) {
        printf("Checking links...\n");
        test_links();
    }


    return 0;
}

void test_leaks() {
    init_all();
    free_all();
}

void test_links() {
    struct listlink *foo = malloc(sizeof (struct listlink));

    int *bar = malloc(sizeof (int));

    foo->prev = NULL;
    foo->next = NULL;

    addlink(foo, bar);
    addlink(foo, bar);
    addlink(foo, bar);

    clearlinks(foo);
    free(bar);
}


