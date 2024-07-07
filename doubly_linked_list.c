#include <stdio.h>

#include "doubly_linked_list.h"

DOUBLY_LINKED_LIST_DECL(int)
void doubly_linked_list_test() {
    DOUBLY_LINKED_LIST(int) dl_int;
    DOUBLY_LINKED_LIST_INIT(int)(&dl_int);

    for(int i=0; i<20; i++)
        DOUBLY_LINKED_LIST_PUSH_END(int)(&dl_int, i);
    while(DOUBLY_LINKED_LIST_SIZE(int)(&dl_int))
        printf("%d ", DOUBLY_LINKED_LIST_POP_END(int)(&dl_int));

    printf("\n");

    for(int i=0; i<20; i++)
        DOUBLY_LINKED_LIST_PUSH_END(int)(&dl_int, i*i);
    while(DOUBLY_LINKED_LIST_SIZE(int)(&dl_int))
        printf("%d ", DOUBLY_LINKED_LIST_POP_FRONT(int)(&dl_int));

    printf("\n");

    for(int i=0; i<20; i++)
        DOUBLY_LINKED_LIST_PUSH_FRONT(int)(&dl_int, i*i*i);
    while(DOUBLY_LINKED_LIST_SIZE(int)(&dl_int))
        printf("%d ", DOUBLY_LINKED_LIST_POP_FRONT(int)(&dl_int));

    printf("\n\n");
}