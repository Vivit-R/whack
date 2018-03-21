#ifndef __DATASTRUCT__
#define __DATASTRUCT__

struct listlink {
    void *elem;
    struct listlink *prev;
    struct listlink *next;
};


/* void removelink(struct listlink *l); */

#endif
