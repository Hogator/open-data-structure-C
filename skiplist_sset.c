#include <stdio.h>

#include "skiplist_sset.h"


SKIPLIST_SSET_DECL(int)
void skiplist_sset_test() {

    SKIPLIST_SSET(int)  s_int;
    SKIPLIST_SSET_INIT(int)(&s_int);

    for(int i=0; i<40; i++)
        SKIPLIST_SSET_ADD(int)(&s_int, i);
    for(int i=0; i<40; i++)
        printf("%d ", SKIPLIST_SSET_FIND(int)(&s_int, i));
    printf("h: %d", s_int.h);

    putchar('\n');

    for(int i=1; i<40; i+=2)
        SKIPLIST_SSET_REMOVE(int)(&s_int, i);
    for(int i=0; i<40; i++)
        printf("%d ", SKIPLIST_SSET_FIND(int)(&s_int, i));
    printf("h: %d", s_int.h);

    putchar('\n');

    for(int i=0; i<40; i+=2)
        SKIPLIST_SSET_REMOVE(int)(&s_int, i);
    for(int i=0; i<40; i++)
        printf("%d ", SKIPLIST_SSET_FIND(int)(&s_int, i));
    printf("h: %d", s_int.h);

    printf("\n\n");
}