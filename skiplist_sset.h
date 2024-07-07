#ifndef SKIPLIST_SSET_H
#define SKIPLIST_SSET_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SKIPLIST_SSET_CONCAT(X, Y)    X##_##Y##_
#define SKIPLIST_SSET_NODE(type) SKIPLIST_SSET_CONCAT(skiplist_sset_node, type)
#define SKIPLIST_SSET(type)   SKIPLIST_SSET_CONCAT(skiplist_sset, type)
#define SKIPLIST_SSET_INIT(type)  SKIPLIST_SSET_CONCAT(skiplist_sset_init, type)
#define SKIPLIST_SSET_FIND(type)   SKIPLIST_SSET_CONCAT(skiplist_sset_find, type)
#define SKIPLIST_SSET_ADD(type)   SKIPLIST_SSET_CONCAT(skiplist_sset_add, type)
#define SKIPLIST_SSET_REMOVE(type)   SKIPLIST_SSET_CONCAT(skiplist_sset_remove, type)

#define SKIPLIST_SSET_DECL(type)    \
typedef struct SKIPLIST_SSET_NODE(type) {   \
    type data;  \
    struct SKIPLIST_SSET_NODE(type)** next;  \
} SKIPLIST_SSET_NODE(type); \
typedef struct SKIPLIST_SSET(type) {    \
    struct SKIPLIST_SSET_NODE(type) sentinel;   \
    int h; \
} SKIPLIST_SSET(type); \
void SKIPLIST_SSET_INIT(type)(SKIPLIST_SSET(type)* ss) {   \
    ss->sentinel.next=NULL; \
    ss->h=-1;    \
    srand(time(0)); \
}   \
bool SKIPLIST_SSET_FIND(type)(SKIPLIST_SSET(type)* ss, type val) { \
    if(ss->h<0) {   \
        return false;   \
    }   \
    SKIPLIST_SSET_NODE(type)* u=&ss->sentinel;  \
    int r=ss->h;   \
    while(r>=0) {   \
        while(u->next[r] && u->next[r]->data<val) { \
            u=u->next[r];   \
        }   \
        r--;    \
    }   \
    return u->next[0]&&u->next[0]->data==val;    \
}   \
bool SKIPLIST_SSET_ADD(type)(SKIPLIST_SSET(type)* ss, type val) {  \
    unsigned int n=rand();  \
    int h=0;   \
    while(n=(n&(n-1))) {   \
        h++;    \
    }   \
    SKIPLIST_SSET_NODE(type)* node=(SKIPLIST_SSET_NODE(type)*)calloc(1, sizeof(SKIPLIST_SSET_NODE(type))); \
    node->data=val; \
    node->next=(SKIPLIST_SSET_NODE(type)**)calloc(h+1, sizeof(SKIPLIST_SSET_NODE(type)*));  \
    SKIPLIST_SSET_NODE(type)** pres=(SKIPLIST_SSET_NODE(type)**)calloc((ss->h<h?h:ss->h)+1, sizeof(SKIPLIST_SSET_NODE(type)*)); \
    SKIPLIST_SSET_NODE(type)* u=&ss->sentinel;  \
    int r=ss->h;   \
    if(ss->h<h) {   \
        ss->sentinel.next=ss->sentinel.next?(SKIPLIST_SSET_NODE(type)**)realloc(ss->sentinel.next, sizeof(SKIPLIST_SSET_NODE(type)*)*(h+1)):(SKIPLIST_SSET_NODE(type)**)calloc(h+1, sizeof(SKIPLIST_SSET_NODE(type)*));    \
        for(int i=h; i>ss->h; i--) {  \
            pres[i]=&ss->sentinel;  \
        }   \
        ss->h=h;    \
    }   \
    while(r>=0) {   \
        while(u->next[r] && u->next[r]->data<val) {  \
            u=u->next[r];   \
        }   \
        if(u->next[r] && u->next[r]->data==val) {    \
            if(pres) {  \
                free(pres); \
            }   \
            return false;   \
        }   \
        pres[r--]=u;    \
    }   \
    for(int i=0; i<=h; i++) {   \
        node->next[i]=pres[i]->next[i];    \
        pres[i]->next[i]=node; \
    }   \
    free(pres); \
    return true;    \
}   \
bool SKIPLIST_SSET_REMOVE(type)(SKIPLIST_SSET(type)* ss, type val) {   \
    SKIPLIST_SSET_NODE(type)* node=NULL;    \
    bool rm=false;  \
    SKIPLIST_SSET_NODE(type)* u=&ss->sentinel;    \
    int r=ss->h;   \
    int new_h=ss->h;   \
    while(r>=0) {   \
        while(u->next[r] && u->next[r]->data<val) { \
            u=u->next[r];   \
        }   \
        if(u->next[r] && u->next[r]->data==val) {   \
            rm=true;    \
            node=u->next[r];   \
            u->next[r]=u->next[r]->next[r]; \
            if(u==&ss->sentinel&&!u->next[r]) { \
                new_h--;    \
            }   \
        }   \
        r--;    \
    }   \
    if(rm) {    \
        free(node); \
    }   \
    if(new_h<0) {    \
        free(ss->sentinel.next);    \
        ss->sentinel.next=NULL; \
    }   \
    else if(new_h<ss->h) {   \
        ss->sentinel.next=(SKIPLIST_SSET_NODE(type)**)realloc(ss->sentinel.next, sizeof(SKIPLIST_SSET_NODE(type)*)*(new_h+1));  \
    }   \
    ss->h=new_h;    \
    return rm;  \
}


void skiplist_sset_test();

#endif