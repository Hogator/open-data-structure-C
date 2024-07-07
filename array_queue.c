#include <stdio.h>

#include "array_queue.h"

ARRAY_QUEUE_DECL(int)
void array_queue_test() {
    ARRAY_QUEUE(int) q_int;
    ARRAY_QUEUE_INIT(int)(&q_int);
    // for(int i=0; i<10; i++)
    //     ARRAY_QUEUE_ADD(int)(&q_int, 0, i*i);
    // for(int i=0; i<10; i++)
    //     printf("%d ", ARRAY_QUEUE_GET(int)(&q_int, i));
    // putchar('\n');
    // for(int i=0; i<20; i++)
    //     ARRAY_QUEUE_PUSH_BACK(int)(&q_int, i+5);
    // for(int i=0; i<15; i++)
    //     printf("%d ", ARRAY_QUEUE_POP_FRONT(int)(&q_int));
    // putchar('\n');
    // for(int i=0; i<10; i++)
    //     ARRAY_QUEUE_PUSH_BACK(int)(&q_int, i-10);
    // for(int i=0; i<15; i++)
    //     printf("%d ", ARRAY_QUEUE_POP_FRONT(int)(&q_int));

    // putchar('\n');

    for(int i=0; i<30; i++)
        ARRAY_QUEUE_PUSH_BACK(int)(&q_int, i);
    for(int i=0; i<20; i++)
        printf("%d ", ARRAY_QUEUE_POP_FRONT(int)(&q_int));
    for(int i=0; i<50; i++)
        ARRAY_QUEUE_PUSH_BACK(int)(&q_int, i+30);
    for(int i=0; i<60; i++)
        printf("%d ", ARRAY_QUEUE_POP_FRONT(int)(&q_int));

    printf("\n\n");
}
