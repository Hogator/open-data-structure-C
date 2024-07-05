#include <stdio.h>

#include "array_stack.h"

ARRAY_STACK_DECL(int)
void array_stack_test() {
    ARRAY_STACK(int) s_int;
    ARRAY_STACK_INIT(int)(&s_int);
    for(int i=0; i<5; i++)
        ARRAY_STACK_ADD(int)(&s_int, 0, i*i);
    for(int i=0; i<5; i++)
        printf("%d ", ARRAY_STACK_GET(int)(&s_int, i));
    putchar('\n');
    for(int i=0; i<5; i++)
        ARRAY_STACK_PUSH(int)(&s_int, i*i*i);
    for(int i=0; i<10; i++)
        printf("%d ", ARRAY_STACK_POP(int)(&s_int));

    printf("\n\n");
}