#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define BINARY_TREE_CONCAT(X, Y)    X##_##Y##_
#define BINARY_TREE(type)   BINARY_TREE_CONCAT(binary_tree, type)
#define BINARY_TREE_INIT(type)  BINARY_TREE_CONCAT(binary_tree_init, type)
#define BINARY_TREE_SIZE(type)  BINARY_TREE_CONCAT(binary_tree_size, type)
#define BINARY_TREE_TRAVERSE(type)   BINARY_TREE_CONCAT(binary_tree_traverse, type)
#define BINARY_TREE_TRAVERSE2(type)   BINARY_TREE_CONCAT(binary_tree_traverse2, type)


#define BINARY_TREE_DECL(type)  \
typedef struct BINARY_TREE(type) { \
    type d; \
    struct BINARY_TREE(type)* left;    \
    struct BINARY_TREE(type)* right;   \
} BINARY_TREE(type);   \
void BINARY_TREE_INIT(type)(BINARY_TREE(type)* p, type v, BINARY_TREE(type)* l, BINARY_TREE(type)* r) { \
    p->d=v; \
    p->left=l;  \
    p->right=r; \
}   \
unsigned int BINARY_TREE_SIZE(type)(BINARY_TREE(type)* p) {   \
    if(!p)  \
        return 0;   \
    return BINARY_TREE_SIZE(type)(p->left)+BINARY_TREE_SIZE(type)(p->right)+1;  \
}   \
void BINARY_TREE_TRAVERSE(type)(BINARY_TREE(type)* p, void (*f)(void*)) {    \
    if(!p)  \
        return; \
    BINARY_TREE_TRAVERSE(type)(p->left, f);    \
    (*f)(&p->d);    \
    BINARY_TREE_TRAVERSE(type)(p->right, f);   \
}   \
void BINARY_TREE_TRAVERSE2(type)(BINARY_TREE(type)* p, void (*f)(void*)) {  \
    if(!p)  \
        return; \
    BINARY_TREE(type)* stack[200];   \
    unsigned int idx=0; \
    stack[idx++]=p; \
    BINARY_TREE(type)* pre=NULL;    \
    BINARY_TREE(type)* cur=NULL;    \
    while(idx>0) {  \
        cur=stack[idx-1];   \
        if(pre==NULL || pre->left==cur || pre->right==cur) {    \
            if(cur->left)   \
                stack[idx++]=cur->left; \
            else if(cur->right) {   \
                (*f)(&cur->d);    \
                stack[idx++]=cur->right;    \
            }   \
            else {  \
                (*f)(&cur->d);    \
                idx--;  \
            }   \
        }   \
        else if(pre==cur->left) {   \
            (*f)(&cur->d);    \
            if(cur->right)  \
                stack[idx++]=cur->right;    \
            else {  \
                idx--;  \
            }   \
        }   \
        else {  \
            idx--;  \
        }   \
        pre=cur;    \
    }   \
}   \



void binary_tree_test();

#endif