#ifndef SKIPLIST_LIST_H
#define SKIPLIST_LIST_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SKIPLIST_LIST_CONCAT(X, Y)    X##_##Y##_
#define SKIPLIST_LIST_NODE(type) SKIPLIST_LIST_CONCAT(skiplist_list_node, type)
#define SKIPLIST_LIST(type)   SKIPLIST_LIST_CONCAT(skiplist_list, type)
#define SKIPLIST_LIST_INIT(type)  SKIPLIST_LIST_CONCAT(skiplist_list_init, type)
#define SKIPLIST_LIST_GET(type)   SKIPLIST_LIST_CONCAT(skiplist_list_get, type)
#define SKIPLIST_LIST_SET(type)   SKIPLIST_LIST_CONCAT(skiplist_list_set, type)
#define SKIPLIST_LIST_ADD(type)   SKIPLIST_LIST_CONCAT(skiplist_list_add, type)
#define SKIPLIST_LIST_REMOVE(type)   SKIPLIST_LIST_CONCAT(skiplist_list_remove, type)
#define SKIPLIST_LIST_PUSH_BACK(type)   SKIPLIST_LIST_CONCAT(skiplist_list_push_back, type)
#define SKIPLIST_LIST_POP_BACK(type)   SKIPLIST_LIST_CONCAT(skiplist_list_pop_back, type)
#define SKIPLIST_LIST_PUSH_FRONT(type)   SKIPLIST_LIST_CONCAT(skiplist_list_push_front, type)
#define SKIPLIST_LIST_POP_FRONT(type)   SKIPLIST_LIST_CONCAT(skiplist_list_pop_front, type)

#define SKIPLIST_LIST_DECL(type)    \
typedef struct SKIPLIST_LIST_NODE(type) {   \
    type data;  \
    struct SKIPLIST_LIST_NODE(type)** next;  \
    unsigned int* gap;  \
} SKIPLIST_LIST_NODE(type); \
typedef struct SKIPLIST_LIST(type) {    \
    struct SKIPLIST_LIST_NODE(type) sentinel;   \
    int h; \
    unsigned int len;   \
} SKIPLIST_LIST(type); \
void SKIPLIST_LIST_INIT(type)(SKIPLIST_LIST(type)* sl) {   \
    sl->sentinel.next=NULL; \
    sl->sentinel.gap=NULL;  \
    sl->h=-1;    \
    sl->len=0;  \
    srand(time(0)); \
}   \
type SKIPLIST_LIST_GET(type)(SKIPLIST_LIST(type)* sl, unsigned int idx) { \
    assert(idx<sl->len);    \
    SKIPLIST_LIST_NODE(type)* u=&sl->sentinel;  \
    int r=sl->h;   \
    while(r>=0) {   \
        while(u->next[r] && idx>=u->gap[r]) { \
            idx-=u->gap[r]; \
            u=u->next[r];   \
        }   \
        r--;    \
    }   \
    return u->next[0]->data;    \
}   \
type SKIPLIST_LIST_SET(type)(SKIPLIST_LIST(type)* sl, unsigned int idx, type val) { \
    assert(idx<sl->len);    \
    SKIPLIST_LIST_NODE(type)* u=&sl->sentinel;  \
    int r=sl->h;   \
    while(r>=0) {   \
        while(u->next[r] && idx>=u->gap[r]) { \
            idx-=u->gap[r]; \
            u=u->next[r];   \
        }   \
        r--;    \
    }   \
    type ret=u->next[0]->data;   \
    u->next[0]->data=val;    \
    return ret;    \
}   \
void SKIPLIST_LIST_ADD(type)(SKIPLIST_LIST(type)* sl, unsigned int idx, type val) {  \
    assert(idx<=sl->len);   \
    unsigned int n=rand();  \
    int h=0;   \
    while(n=(n&(n-1))) {   \
        h++;    \
    }   \
    SKIPLIST_LIST_NODE(type)* node=(SKIPLIST_LIST_NODE(type)*)calloc(1, sizeof(SKIPLIST_LIST_NODE(type))); \
    node->data=val; \
    node->next=(SKIPLIST_LIST_NODE(type)**)calloc(h+1, sizeof(SKIPLIST_LIST_NODE(type)*));  \
    node->gap=(unsigned int*)calloc(h+1, sizeof(unsigned int)); \
    if(sl->h<h) {   \
        sl->sentinel.next=sl->sentinel.next?(SKIPLIST_LIST_NODE(type)**)realloc(sl->sentinel.next, sizeof(SKIPLIST_LIST_NODE(type)*)*(h+1)):(SKIPLIST_LIST_NODE(type)**)calloc(h+1, sizeof(SKIPLIST_LIST_NODE(type)*));    \
        sl->sentinel.gap=sl->sentinel.gap?(unsigned int*)realloc(sl->sentinel.gap, sizeof(unsigned int)*(h+1)):(unsigned int*)calloc(h+1, sizeof(unsigned int));    \
        sl->h=h;    \
    }   \
    SKIPLIST_LIST_NODE(type)* u=&sl->sentinel;  \
    int r=sl->h;   \
    while(r>=0) {   \
        while(u->next[r] && idx>=u->gap[r]) {  \
            idx-=u->gap[r]; \
            u=u->next[r];   \
        }   \
        u->gap[r]++;    \
        if(r<=h) {  \
            node->next[r]=u->next[r];   \
            u->next[r]=node;    \
            node->gap[r]=u->gap[r]-idx-1; \
            u->gap[r]=idx+1;  \
        }   \
        r--;    \
    }   \
    sl->len++;  \
}   \
type SKIPLIST_LIST_REMOVE(type)(SKIPLIST_LIST(type)* sl, unsigned int idx) {   \
    assert(idx<sl->len);    \
    SKIPLIST_LIST_NODE(type)* node=NULL;    \
    SKIPLIST_LIST_NODE(type)* u=&sl->sentinel;    \
    int r=sl->h;   \
    int new_h=sl->h;   \
    type ret;   \
    while(r>=0) {   \
        while(u->next[r] && idx>=u->gap[r]) { \
            idx-=u->gap[r]; \
            u=u->next[r];   \
        }   \
        u->gap[r]--;    \
        if(idx==u->gap[r] && u->next[r]) {   \
            node=u->next[r];    \
            ret=u->next[r]->data;    \
            u->gap[r]=u->gap[r]+u->next[r]->gap[r]; \
            u->next[r]=u->next[r]->next[r]; \
            if(u==&sl->sentinel&&!u->next[r]) { \
                new_h--;    \
            }   \
        }   \
        r--;    \
    }   \
    free(node); \
    if(new_h<0) {    \
        free(sl->sentinel.next);    \
        sl->sentinel.next=NULL; \
    }   \
    else if(new_h<sl->h) {   \
        sl->sentinel.next=(SKIPLIST_LIST_NODE(type)**)realloc(sl->sentinel.next, sizeof(SKIPLIST_LIST_NODE(type)*)*(new_h+1));  \
    }   \
    sl->h=new_h;    \
    sl->len--;  \
    return ret;  \
}   \
void SKIPLIST_LIST_PUSH_BACK(type)(SKIPLIST_LIST(type)* sl, type val) {   \
    SKIPLIST_LIST_ADD(type)(sl, sl->len, val);    \
}   \
type SKIPLIST_LIST_POP_BACK(type)(SKIPLIST_LIST(type)* sl) {   \
    return SKIPLIST_LIST_REMOVE(type)(sl, sl->len-1);    \
}   \
void SKIPLIST_LIST_PUSH_FRONT(type)(SKIPLIST_LIST(type)* sl, type val) {   \
    SKIPLIST_LIST_ADD(type)(sl, 0, val);    \
}   \
type SKIPLIST_LIST_POP_FRONT(type)(SKIPLIST_LIST(type)* sl) {   \
    return SKIPLIST_LIST_REMOVE(type)(sl, 0);    \
}   \


void skiplist_list_test();

#endif