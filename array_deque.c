#include <stdio.h>

#include "array_deque.h"

ARRAY_DEQUE_DECL(int)
void array_deque_test() {
    ARRAY_DEQUE(int) q_int;
    ARRAY_DEQUE_INIT(int)(&q_int);

    // for(int i=0; i<10; i++)
    //     ARRAY_DEQUE_ADD(int)(&q_int, 0, i*i);
    // for(int i=0; i<10; i++)
    //     printf("%d ", ARRAY_DEQUE_GET(int)(&q_int, i));
    // putchar('\n');
    // for(int i=0; i<20; i++)
    //     ARRAY_DEQUE_PUSH_BACK(int)(&q_int, i+5);
    // for(int i=0; i<15; i++)
    //     printf("%d ", ARRAY_DEQUE_POP_FRONT(int)(&q_int));
    // putchar('\n');
    // for(int i=0; i<10; i++)
    //     ARRAY_DEQUE_PUSH_BACK(int)(&q_int, i-10);
    // for(int i=0; i<15; i++)
    //     printf("%d ", ARRAY_DEQUE_POP_FRONT(int)(&q_int));


    for(int i=0; i<10; i++)
        ARRAY_DEQUE_PUSH_BACK(int)(&q_int, i*i);
    for(int i=0; i<10; i++)
        ARRAY_DEQUE_PUSH_FRONT(int)(&q_int, i*i*i);
    for(int i=0; i<15; i++)
        printf("%d ", ARRAY_DEQUE_POP_FRONT(int)(&q_int));
    for(int i=0; i<5; i++)
        printf("%d ", ARRAY_DEQUE_POP_BACK(int)(&q_int));

    printf("\n\n");
}
