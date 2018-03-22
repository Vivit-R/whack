#ifndef __DATASTRUCT__
#define __DATASTRUCT__

struct listlink {
    void *elem;
    struct listlink *prev;
    struct listlink *next;
};

void addlink(struct listlink *l, void *elem);
void removelink(struct listlink *l);
void clearlinks(struct listlink *l, void (*op)(void*));


#endif
