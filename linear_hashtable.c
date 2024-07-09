#include <stdio.h>

#include "linear_hashtable.h"

LINEAR_HASHTABLE_DECL(int)
void linear_hashtable_test() {

    LINEAR_HASHTABLE(int) lt_int;
    LINEAR_HASHTABLE_INIT(int)(&lt_int);

    for(int i=0; i<40; i++)
        LINEAR_HASHTABLE_ADD(int)(&lt_int, i);

    for(int i=0; i<40; i++)
        printf("%d ", LINEAR_HASHTABLE_FIND(int)(&lt_int, i));

    putchar('\n');

    for(int i=0; i<40; i+=2)
        LINEAR_HASHTABLE_REMOVE(int)(&lt_int, i);

    for(int i=0; i<40; i++)
        printf("%d ", LINEAR_HASHTABLE_FIND(int)(&lt_int, i));

    LINEAR_HASHTABLE_FREE(int)(&lt_int);

    printf("\n\n");
}