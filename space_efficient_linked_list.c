#include <stdio.h>

#include "space_efficient_linked_list.h"


SPACE_EFFICIENT_LINKED_LIST_FIXED_DECL(int)
SPACE_EFFICIENT_LINKED_LIST_DECL(int)
void space_efficient_linked_list_test() {

    SPACE_EFFICIENT_LINKED_LIST_FIXED(int) q_int;
    SPACE_EFFICIENT_LINKED_LIST_FIXED_INIT(int)(&q_int, 20);

    for(int i=0; i<20; i++)
        SPACE_EFFICIENT_LINKED_LIST_FIXED_PUSH_BACK(int)(&q_int, i);
    for(int i=0; i<20; i++)
        printf("%d ", SPACE_EFFICIENT_LINKED_LIST_FIXED_POP_BACK(int)(&q_int));

    putchar('\n');

    SPACE_EFFICIENT_LINKED_LIST(int) l_int;
    SPACE_EFFICIENT_LINKED_LIST_INIT(int)(&l_int, 5);

    for(int i=0; i<13; i++)
        SPACE_EFFICIENT_LINKED_LIST_ADD(int)(&l_int, 0, i);
    for(int i=13; i<30; i++)
        SPACE_EFFICIENT_LINKED_LIST_ADD(int)(&l_int, i, i);
    for(int i=0; i<30; i++)
        printf("%d ", SPACE_EFFICIENT_LINKED_LIST_GET(int)(&l_int, i));

    printf("\n\n");
}