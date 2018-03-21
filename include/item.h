#ifndef __ITEM__
#define __ITEM__

#define ITEM_SCROLL '?'
#define ITEM_FOOD '%'
#define ITEM_WEAPON '('

/* Specific type of item 
 * (e.g. scroll of identify, potion of healing, iron shortsword) */
struct itype {
    char glyph; /* Also represents the class of item */

    int properties[3];

    /* Name when identified and when unidentified, respectively */
    char *idname;
    char *unidname;

    /* Player informal identification */
    char *inscribe;
};

extern struct itype *itypes;

/* Specific instance of an item */
typedef struct t_item {
    char glyph;

    int ench;
    struct itype itype;

    /* Item's name as an artifact (e.g. "Excalibur") */
    /* If null, then the item isn't an artifact */
    char *artname;

    /* Player inscription (notes) */
    char *inscribe;
} item;

#endif
