#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define DOUBLY_LINKED_LIST_CONCAT(X, Y)    X##_##Y##_
#define DOUBLY_LINKED_LIST_NODE(type)   DOUBLY_LINKED_LIST_CONCAT(doubly_linked_list_node, type)
#define DOUBLY_LINKED_LIST_NODE_INIT(type)   DOUBLY_LINKED_LIST_CONCAT(doubly_linked_list_node_init, type)
#define DOUBLY_LINKED_LIST(type)   DOUBLY_LINKED_LIST_CONCAT(doubly_linked_list, type)
#define DOUBLY_LINKED_LIST_INIT(type)  DOUBLY_LINKED_LIST_CONCAT(doubly_linked_list_init, type)
#define DOUBLY_LINKED_LIST_SIZE(type)  DOUBLY_LINKED_LIST_CONCAT(doubly_linked_list_size, type)
#define DOUBLY_LINKED_LIST_PUSH_END(type)   DOUBLY_LINKED_LIST_CONCAT(doubly_linked_list_push_end, type)
#define DOUBLY_LINKED_LIST_POP_END(type)   DOUBLY_LINKED_LIST_CONCAT(doubly_linked_list_pop_end, type)
#define DOUBLY_LINKED_LIST_PUSH_FRONT(type)   DOUBLY_LINKED_LIST_CONCAT(doubly_linked_list_push_front, type)
#define DOUBLY_LINKED_LIST_POP_FRONT(type)   DOUBLY_LINKED_LIST_CONCAT(doubly_linked_list_pop_front, type)

#define DOUBLY_LINKED_LIST_DECL(type)  \
typedef struct DOUBLY_LINKED_LIST_NODE(type) {  \
    type data;  \
    struct DOUBLY_LINKED_LIST_NODE(type)* next; \
    struct DOUBLY_LINKED_LIST_NODE(type)* pre;  \
} DOUBLY_LINKED_LIST_NODE(type);    \
void DOUBLY_LINKED_LIST_NODE_INIT(type)(DOUBLY_LINKED_LIST_NODE(type)* node, type val, DOUBLY_LINKED_LIST_NODE(type)* ptr_n, DOUBLY_LINKED_LIST_NODE(type)* ptr_p) {   \
    node->data=val; \
    node->next=ptr_n;   \
    node->pre=ptr_p;    \
    ptr_n->pre=node;    \
    ptr_p->next=node;   \
}   \
typedef struct DOUBLY_LINKED_LIST(type) {   \
    DOUBLY_LINKED_LIST_NODE(type) head; \
    unsigned int len;   \
} DOUBLY_LINKED_LIST(type);    \
void DOUBLY_LINKED_LIST_INIT(type)(DOUBLY_LINKED_LIST(type)* dl) { \
    dl->head.next=&dl->head;  \
    dl->head.pre=&dl->head;   \
    dl->len=0;   \
}   \
unsigned int DOUBLY_LINKED_LIST_SIZE(type)(DOUBLY_LINKED_LIST(type)* dl) {   \
    return dl->len;  \
}   \
void DOUBLY_LINKED_LIST_PUSH_END(type)(DOUBLY_LINKED_LIST(type)* dl, type val) {   \
    DOUBLY_LINKED_LIST_NODE(type)* node=(DOUBLY_LINKED_LIST_NODE(type)*)malloc(sizeof(DOUBLY_LINKED_LIST_NODE(type)));  \
    DOUBLY_LINKED_LIST_NODE_INIT(type)(node, val, &dl->head, dl->head.pre);    \
    dl->len++;   \
}   \
type DOUBLY_LINKED_LIST_POP_END(type)(DOUBLY_LINKED_LIST(type)* dl) {  \
    assert(dl->len); \
    DOUBLY_LINKED_LIST_NODE(type)* node=dl->head.pre;    \
    type ret=node->data; \
    dl->head.pre=node->pre;   \
    dl->head.pre->next=&dl->head; \
    free(node); \
    dl->len--;   \
    return ret;  \
}   \
void DOUBLY_LINKED_LIST_PUSH_FRONT(type)(DOUBLY_LINKED_LIST(type)* dl, type val) {   \
    DOUBLY_LINKED_LIST_NODE(type)* node=(DOUBLY_LINKED_LIST_NODE(type)*)malloc(sizeof(DOUBLY_LINKED_LIST_NODE(type)));  \
    DOUBLY_LINKED_LIST_NODE_INIT(type)(node, val, dl->head.next, &dl->head);    \
    dl->len++;   \
}   \
type DOUBLY_LINKED_LIST_POP_FRONT(type)(DOUBLY_LINKED_LIST(type)* dl) {  \
    assert(dl->len); \
    DOUBLY_LINKED_LIST_NODE(type)* node=dl->head.next;    \
    type ret=node->data; \
    dl->head.next=node->next;    \
    dl->head.next->pre=&dl->head;   \
    free(node); \
    dl->len--;   \
    return ret;  \
}


void doubly_linked_list_test();

#endif