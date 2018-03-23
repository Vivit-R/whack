#include <stdlib.h>
#include "datastruct.h"

/* Adds a link to the linked list after given link l. */
void addlink(struct listlink *l, void *elem) {
    struct listlink *this = malloc(sizeof (struct listlink));
    this->elem = elem;
    this->prev = l;

    /* If l is null, we're being added at the end of a list. */
    if (l) {
        this->next = l->next;
        l->next = this;
    } else {
        this->next = NULL;
    }

    /* If we are at the end of the list, this->next will be NULL, and this
     * statement will not execute. Otherwise, it will connect the following
     * element in the linked list to this one. */
    if (this->next)
        this->next->prev = this;
}

/* Does NOT free the element, only the link itself. */
void rmlink(struct listlink *l) {
    if (l->prev) l->prev->next = l->next;
    if (l->next) l->next->prev = l->prev;
    free(l);
    l = NULL;
}

/* Removes all links in a linked list containing the given element.
 * If function pointer op is not null, execute it on l->elem before removing
 * l. */
void clearlinks(struct listlink *l, void (*op)(void*)) {
    if (!l) return;

    struct listlink *rm_next = 
        l->prev ? l->prev :
        l->next ? l->next :
        NULL; 

    if (op) {
        op(l->elem);
    }

    rmlink(l);
    clearlinks(rm_next, op);
}

