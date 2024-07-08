#ifndef CHAINED_HASHTABLE_H
#define CHAINED_HASHTABLE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#define CHAINED_HASHTABLE_CONCAT(X, Y)    X##_##Y##_
#define CHAINED_HASHTABLE_NODE(type) CHAINED_HASHTABLE_CONCAT(chained_hashtable_node, type)
#define CHAINED_HASHTABLE(type)   CHAINED_HASHTABLE_CONCAT(chained_hashtable, type)
#define CHAINED_HASHTABLE_INIT(type)  CHAINED_HASHTABLE_CONCAT(chained_hashtable_init, type)
#define CHAINED_HASHTABLE_HASH(type)    CHAINED_HASHTABLE_CONCAT(chained_hashtable_hash, type)
#define CHAINED_HASHTABLE_RESIZE(type)   CHAINED_HASHTABLE_CONCAT(chained_hashtable_resize, type)
#define CHAINED_HASHTABLE_FIND(type)   CHAINED_HASHTABLE_CONCAT(chained_hashtable_find, type)
#define CHAINED_HASHTABLE_ADD(type)   CHAINED_HASHTABLE_CONCAT(chained_hashtable_add, type)
#define CHAINED_HASHTABLE_REMOVE(type)   CHAINED_HASHTABLE_CONCAT(chained_hashtable_remove, type)
#define CHAINED_HASHTABLE_FREE(type)   CHAINED_HASHTABLE_CONCAT(chained_hashtable_free, type)


#define CHAINED_HASHTABLE_DECL(type)    \
typedef struct CHAINED_HASHTABLE_NODE(type) {   \
    type d; \
    struct CHAINED_HASHTABLE_NODE(type)* next;  \
} CHAINED_HASHTABLE_NODE(type); \
typedef struct CHAINED_HASHTABLE(type) {    \
    unsigned int d; \
    CHAINED_HASHTABLE_NODE(type)* t;    \
    uint32_t z;   \
    unsigned int n; \
} CHAINED_HASHTABLE(type);  \
void CHAINED_HASHTABLE_INIT(type)(CHAINED_HASHTABLE(type)* ct) {    \
    ct->d=0; \
    ct->t=(CHAINED_HASHTABLE_NODE(type)*)calloc(1ul<<ct->d, sizeof(CHAINED_HASHTABLE_NODE(type)));   \
    srand(time(0));    \
    ct->z=rand()|1; \
    ct->n=0;    \
}   \
unsigned int CHAINED_HASHTABLE_HASH(type)(CHAINED_HASHTABLE(type)* ct, type x) { \
    return ((uint64_t)ct->z*x)>>(32-ct->d)&((1ul<<ct->d)-1); \
}   \
void CHAINED_HASHTABLE_RESIZE(type)(CHAINED_HASHTABLE(type)* ct, bool grow) {    \
    uint64_t cap=1ul<<ct->d; \
    uint64_t new_cap=1ul<<(grow?++ct->d:--ct->d); \
    CHAINED_HASHTABLE_NODE(type)* new_t=(CHAINED_HASHTABLE_NODE(type)*)calloc(new_cap, sizeof(CHAINED_HASHTABLE_NODE(type)));   \
    for(int i=0; i<cap; i++) {  \
        CHAINED_HASHTABLE_NODE(type)* node;   \
        while(ct->t[i].next) { \
            node=ct->t[i].next; \
            ct->t[i].next=node->next;   \
            unsigned int idx=CHAINED_HASHTABLE_HASH(type)(ct, node->d);   \
            node->next=new_t[idx].next; \
            new_t[idx].next=node;  \
        }   \
    }   \
    free(ct->t);    \
    ct->t=new_t;    \
}   \
bool CHAINED_HASHTABLE_FIND(type)(CHAINED_HASHTABLE(type)* ct, type val) {    \
    unsigned int idx=CHAINED_HASHTABLE_HASH(type)(ct, val);   \
    CHAINED_HASHTABLE_NODE(type)* node=&ct->t[idx];    \
    while(node->next && node->next->d!=val) \
        node=node->next;    \
    return node->next;  \
}   \
bool CHAINED_HASHTABLE_ADD(type)(CHAINED_HASHTABLE(type)* ct, type val) {    \
    uint64_t cap=1ul<<ct->d; \
    if(ct->n==cap)  \
        CHAINED_HASHTABLE_RESIZE(type)(ct, true); \
    unsigned int idx=CHAINED_HASHTABLE_HASH(type)(ct, val);   \
    CHAINED_HASHTABLE_NODE(type)* node=&ct->t[idx];    \
    while(node->next && node->next->d!=val) \
        node=node->next;    \
    if(node->next)  \
        return false;   \
    node=(CHAINED_HASHTABLE_NODE(type)*)calloc(1, sizeof(CHAINED_HASHTABLE_NODE(type)));    \
    node->d=val;    \
    node->next=ct->t[idx].next; \
    ct->t[idx].next=node;   \
    ct->n++;    \
    return true;    \
}   \
bool CHAINED_HASHTABLE_REMOVE(type)(CHAINED_HASHTABLE(type)* ct, type val) {    \
    unsigned int idx=CHAINED_HASHTABLE_HASH(type)(ct, val);   \
    CHAINED_HASHTABLE_NODE(type)* node=&ct->t[idx];    \
    while(node->next && node->next->d!=val) \
        node=node->next;    \
    if(!node->next)   \
        return false;   \
    CHAINED_HASHTABLE_NODE(type)* p=node->next; \
    node->next=p->next; \
    free(p);    \
    ct->n--;    \
    uint64_t cap=1ul<<ct->d; \
    if(ct->n*3<cap) \
        CHAINED_HASHTABLE_RESIZE(type)(ct, false); \
    return true;    \
}   \
void CHAINED_HASHTABLE_FREE(type)(CHAINED_HASHTABLE(type)* ct) {    \
    unsigned int cap=1ul<<ct->d;    \
    for(int i=0; i<cap; i++) {  \
        CHAINED_HASHTABLE_NODE(type)* node; \
        while(ct->t[i].next) {    \
            node=ct->t[i].next;   \
            ct->t[i].next=node->next; \
            free(node); \
        }   \
    }   \
    free(ct->t);    \
    ct->d=0;    \
    ct->t=NULL; \
    ct->z=0;    \
    ct->n=0;    \
}   \


void chained_hashtable_test();

#endif