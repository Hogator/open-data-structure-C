#include <stdio.h>

#include "binary_tree.h"


static void pri(void* p) {
    int v=*(int*)p;
    printf("%d ", v);
}

BINARY_TREE_DECL(int)
void binary_tree_test() {

    BINARY_TREE(int) node[20];

    int idx[20]={
        0, 1, 2, 3, 4,
        5, 6, 7, 8, 9,
        10, 11, 12, 13, 14,
        15, 16, 17, 18, 19,
    };
    int left[20]={
        -1, 0, -1, 1, -1,
        3, -1, -1, -1, 6,
        5, 12, -1, -1, 13,
        -1, 14, -1, 17, -1,
    };
    int right[20]={
        -1, 2, -1, 4, -1,
        9, 7, 8, -1, -1,
        11, 16, -1, -1, 15,
        -1, 18, -1, 19, -1,
    };
    for(int i=0; i<20; i++) {
        BINARY_TREE(int)* lcld=left[i]<0?NULL:&node[left[i]];
        BINARY_TREE(int)* rcld=right[i]<0?NULL:&node[right[i]];
        BINARY_TREE_INIT(int)(&node[idx[i]], i, lcld, rcld);
    }

    BINARY_TREE_TRAVERSE(int)(&node[10], pri);
    putchar('\n');

    BINARY_TREE_TRAVERSE2(int)(&node[10], pri);

    printf("\n\n");
}