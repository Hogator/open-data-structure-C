#include <stdio.h>

#include "space_efficient_linked_list.h"


SPACE_EFFICIENT_LINKED_LIST_DECL(int)
void space_efficient_linked_list_test() {

    SPACE_EFFICIENT_LINKED_LIST(int) l_int;
    SPACE_EFFICIENT_LINKED_LIST_INIT(int)(&l_int, 5);

    // for(int i=0; i<13; i++)
    //     SPACE_EFFICIENT_LINKED_LIST_ADD(int)(&l_int, 0, i);
    // for(int i=13; i<30; i++)
    //     SPACE_EFFICIENT_LINKED_LIST_ADD(int)(&l_int, i, i);
    // for(int i=0; i<30; i++)
    //     printf("%d ", SPACE_EFFICIENT_LINKED_LIST_GET(int)(&l_int, i));
    // putchar('\n');
    // for(int i=0; i<30; i++)
    //     printf("%d ", SPACE_EFFICIENT_LINKED_LIST_REMOVE(int)(&l_int, SPACE_EFFICIENT_LINKED_LIST_SIZE(int)(&l_int)-1));


    for(int i=0; i<30; i++)
        SPACE_EFFICIENT_LINKED_LIST_PUSH_BACK(int)(&l_int, i);
    for(int i=0; i<30; i++)
        printf("%d ", SPACE_EFFICIENT_LINKED_LIST_POP_BACK(int)(&l_int));
    
    putchar('\n');

    for(int i=0; i<30; i++)
        SPACE_EFFICIENT_LINKED_LIST_PUSH_BACK(int)(&l_int, i);
    for(int i=0; i<30; i++)
        printf("%d ", SPACE_EFFICIENT_LINKED_LIST_POP_FRONT(int)(&l_int));


    printf("\n\n");
}