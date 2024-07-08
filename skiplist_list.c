#include <stdio.h>

#include "skiplist_list.h"


SKIPLIST_LIST_DECL(int)
void skiplist_list_test() {

    SKIPLIST_LIST(int) sl_int;
    SKIPLIST_LIST_INIT(int)(&sl_int);

    for(int i=0; i<20; i++)
        SKIPLIST_LIST_ADD(int)(&sl_int, i, i*2);
    for(int i=0; i<20; i++)
        SKIPLIST_LIST_ADD(int)(&sl_int, i*2+1, -(i*2+1));

    for(int i=0; i<40; i++)
        printf("%d ", SKIPLIST_LIST_GET(int)(&sl_int, i));

    putchar('\n');

    for(int i=0; i<40; i++)
        printf("%d ", SKIPLIST_LIST_REMOVE(int)(&sl_int, 0));

    putchar('\n');

    for(int i=0; i<20; i++)
        SKIPLIST_LIST_PUSH_BACK(int)(&sl_int, i);
    for(int i=0; i<20; i++)
        printf("%d ", SKIPLIST_LIST_POP_BACK(int)(&sl_int));

    printf("\n\n");
}