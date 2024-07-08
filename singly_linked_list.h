#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define SINGLY_LINKED_LIST_CONCAT(X, Y)    X##_##Y##_
#define SINGLY_LINKED_LIST_NODE(type)   SINGLY_LINKED_LIST_CONCAT(singly_linked_list_node, type)
#define SINGLY_LINKED_LIST_NODE_INIT(type)   SINGLY_LINKED_LIST_CONCAT(singly_linked_list_node_init, type)
#define SINGLY_LINKED_LIST(type)   SINGLY_LINKED_LIST_CONCAT(singly_linked_list, type)
#define SINGLY_LINKED_LIST_INIT(type)  SINGLY_LINKED_LIST_CONCAT(singly_linked_list_init, type)
#define SINGLY_LINKED_LIST_SIZE(type)  SINGLY_LINKED_LIST_CONCAT(singly_linked_list_size, type)
#define SINGLY_LINKED_LIST_ADD(type)   SINGLY_LINKED_LIST_CONCAT(singly_linked_list_add, type)
#define SINGLY_LINKED_LIST_REMOVE(type)   SINGLY_LINKED_LIST_CONCAT(singly_linked_list_remove, type)
#define SINGLY_LINKED_LIST_PUSH(type)   SINGLY_LINKED_LIST_CONCAT(singly_linked_list_push, type)
#define SINGLY_LINKED_LIST_POP(type)   SINGLY_LINKED_LIST_CONCAT(singly_linked_list_pop, type)

#define SINGLY_LINKED_LIST_DECL(type)  \
typedef struct SINGLY_LINKED_LIST_NODE(type) {  \
    type data;  \
    struct SINGLY_LINKED_LIST_NODE(type)* next; \
} SINGLY_LINKED_LIST_NODE(type);    \
void SINGLY_LINKED_LIST_NODE_INIT(type)(SINGLY_LINKED_LIST_NODE(type)* node, type val, SINGLY_LINKED_LIST_NODE(type)* ptr) {   \
    node->data=val;  \
    node->next=ptr;  \
}   \
typedef struct SINGLY_LINKED_LIST(type) {   \
    SINGLY_LINKED_LIST_NODE(type)* head;    \
    SINGLY_LINKED_LIST_NODE(type)* tail;    \
    unsigned int len;   \
} SINGLY_LINKED_LIST(type);    \
void SINGLY_LINKED_LIST_INIT(type)(SINGLY_LINKED_LIST(type)* sl) { \
    sl->head=NULL;   \
    sl->tail=NULL;   \
    sl->len=0;   \
}   \
unsigned int SINGLY_LINKED_LIST_SIZE(type)(SINGLY_LINKED_LIST(type)* sl) {   \
    return sl->len;  \
}   \
void SINGLY_LINKED_LIST_ADD(type)(SINGLY_LINKED_LIST(type)* sl, type val) {  \
    SINGLY_LINKED_LIST_NODE(type)* node=(SINGLY_LINKED_LIST_NODE(type)*)malloc(sizeof(SINGLY_LINKED_LIST_NODE(type)));  \
    SINGLY_LINKED_LIST_NODE_INIT(type)(node, val, NULL);  \
    if(!sl->len)    \
        sl->head=node;   \
    else    \
        sl->tail->next=node; \
    sl->tail=node;   \
    sl->len++;   \
}   \
type SINGLY_LINKED_LIST_REMOVE(type)(SINGLY_LINKED_LIST(type)* sl) { \
    assert(sl->len>0); \
    SINGLY_LINKED_LIST_NODE(type)* node=sl->head;    \
    type ret=node->data;    \
    sl->head=node->next; \
    if(!sl->len)    \
        sl->tail=NULL;   \
    free(node); \
    sl->len--;   \
    return ret; \
}   \
void SINGLY_LINKED_LIST_PUSH(type)(SINGLY_LINKED_LIST(type)* sl, type val) {   \
    SINGLY_LINKED_LIST_NODE(type)* node=(SINGLY_LINKED_LIST_NODE(type)*)malloc(sizeof(SINGLY_LINKED_LIST_NODE(type)));  \
    SINGLY_LINKED_LIST_NODE_INIT(type)(node, val, sl->head);  \
    if(!sl->tail)    \
        sl->tail=node;   \
    sl->head=node;   \
    sl->len++;   \
}   \
type SINGLY_LINKED_LIST_POP(type)(SINGLY_LINKED_LIST(type)* sl) {  \
    return SINGLY_LINKED_LIST_REMOVE(type)(sl);  \
}   \


void singly_linked_list_test();

#endif