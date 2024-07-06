#include <stdio.h>

#include "rootish_array_stack.h"


ROOTISH_ARRAY_STACK_DECL(int)
void rootish_array_stack_test() {
    ROOTISH_ARRAY_STACK(int) s_int;
    ROOTISH_ARRAY_STACK_INIT(int)(&s_int);
    for(int i=0; i<20; i++)
        ROOTISH_ARRAY_STACK_PUSH(int)(&s_int, i);
    for(int i=0; i<20; i++)
        printf("%d ", ROOTISH_ARRAY_STACK_POP(int)(&s_int));

    putchar('\n');

    for(int i=0; i<8; i++)
        ROOTISH_ARRAY_STACK_PUSH(int)(&s_int, i*i);
    ROOTISH_ARRAY_STACK_ADD(int)(&s_int, 2, 22);
    ROOTISH_ARRAY_STACK_ADD(int)(&s_int, 5, 33);
    for(int i=0; i<10; i++)
        printf("%d ", ROOTISH_ARRAY_STACK_POP(int)(&s_int));

    printf("\n\n");
}