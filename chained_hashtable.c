#include <stdio.h>

#include "chained_hashtable.h"

CHAINED_HASHTABLE_DECL(int)
void chained_hashtable_test() {

    CHAINED_HASHTABLE(int) ct_int;
    CHAINED_HASHTABLE_INIT(int)(&ct_int);

    for(int i=0; i<40; i++)
        CHAINED_HASHTABLE_ADD(int)(&ct_int, i);

    for(int i=0; i<40; i++)
        printf("%d ", CHAINED_HASHTABLE_FIND(int)(&ct_int, i));

    putchar('\n');

    for(int i=0; i<40; i+=2)
        CHAINED_HASHTABLE_REMOVE(int)(&ct_int, i);

    for(int i=0; i<40; i++)
        printf("%d ", CHAINED_HASHTABLE_FIND(int)(&ct_int, i));


    printf("\n\n");
}