#include <stdio.h>

#include "singly_linked_list.h"

SINGLY_LINKED_LIST_DECL(int)
void singly_linked_list_test() {
    SINGLY_LINKED_LIST(int) sl_int;
    SINGLY_LINKED_LIST_INIT(int)(&sl_int);
    for(int i=0; i<20; i++)
        SINGLY_LINKED_LIST_ADD(int)(&sl_int, i);
    for(int i=0; i<20; i++)
        printf("%d ", SINGLY_LINKED_LIST_REMOVE(int)(&sl_int));

    putchar('\n');

    for(int i=0; i<20; i++)
        SINGLY_LINKED_LIST_PUSH(int)(&sl_int, i);
    for(int i=0; i<20; i++)
        printf("%d ", SINGLY_LINKED_LIST_POP(int)(&sl_int));

    printf("\n\n");
}