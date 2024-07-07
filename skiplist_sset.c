#include <stdio.h>

#include "skiplist_sset.h"


SKIPLIST_SSET_DECL(int)
void skiplist_sset_test() {

    SKIPLIST_SSET(int)  s_int;
    SKIPLIST_SSET_INIT(int)(&s_int);

    printf("%d ", SKIPLIST_SSET_ADD(int)(&s_int, 1));
    printf("%d ", SKIPLIST_SSET_ADD(int)(&s_int, 2));
    printf("%d ", SKIPLIST_SSET_ADD(int)(&s_int, 3));
    printf("%d ", SKIPLIST_SSET_ADD(int)(&s_int, 4));
    printf("%d ", SKIPLIST_SSET_ADD(int)(&s_int, 1));

    printf("%d ", SKIPLIST_SSET_REMOVE(int)(&s_int, 3));
    // printf("%d ", SKIPLIST_SSET_REMOVE(int)(&s_int, 4));

    putchar('\n');

    printf("%d ", SKIPLIST_SSET_FIND(int)(&s_int, 1));
    printf("%d ", SKIPLIST_SSET_FIND(int)(&s_int, 2));
    printf("%d ", SKIPLIST_SSET_FIND(int)(&s_int, 3));
    printf("%d ", SKIPLIST_SSET_FIND(int)(&s_int, 4));
    printf("%d ", SKIPLIST_SSET_FIND(int)(&s_int, 5));

    printf("\n\n");
}