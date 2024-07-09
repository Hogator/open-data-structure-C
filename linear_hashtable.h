#ifndef LINEAR_HASHTABLE_H
#define LINEAR_HASHTABLE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#define LINEAR_HASHTABLE_CONCAT(X,Y)    X##_##Y##_
#define LINEAR_HASHTABLE_NODE(type)  LINEAR_HASHTABLE_CONCAT(linear_hashtable_node, type)
#define LINEAR_HASHTABLE(type)  LINEAR_HASHTABLE_CONCAT(linear_hashtable, type)
#define LINEAR_HASHTABLE_INIT(type) LINEAR_HASHTABLE_CONCAT(linear_hashtable_init, type)
#define LINEAR_HASHTABLE_HASH(type) LINEAR_HASHTABLE_CONCAT(linear_hashtable_hash, type)
#define LINEAR_HASHTABLE_RESIZE(type) LINEAR_HASHTABLE_CONCAT(linear_hashtable_resize, type)
#define LINEAR_HASHTABLE_FIND(type) LINEAR_HASHTABLE_CONCAT(linear_hashtable_find, type)
#define LINEAR_HASHTABLE_ADD(type) LINEAR_HASHTABLE_CONCAT(linear_hashtable_add, type)
#define LINEAR_HASHTABLE_REMOVE(type) LINEAR_HASHTABLE_CONCAT(linear_hashtable_remove, type)
#define LINEAR_HASHTABLE_FREE(type) LINEAR_HASHTABLE_CONCAT(linear_hashtable_free, type)

#define LINEAR_HASHTABLE_NULL_NODE  0
#define LINEAR_HASHTABLE_DATA_NODE  1
#define LINEAR_HASHTABLE_DEL_NODE   2
#define LINEAR_HASHTABLE_DECL(type) \
typedef struct LINEAR_HASHTABLE_NODE(type) { \
    uint8_t t;  \
    type v; \
} LINEAR_HASHTABLE_NODE(type);  \
typedef struct LINEAR_HASHTABLE(type) { \
    unsigned int d; \
    LINEAR_HASHTABLE_NODE(type)* t;    \
    uint32_t z;   \
    unsigned int q; \
    unsigned int n; \
} LINEAR_HASHTABLE(type);   \
void LINEAR_HASHTABLE_INIT(type)(LINEAR_HASHTABLE(type)* lt) {  \
    lt->d=0;    \
    lt->t=(LINEAR_HASHTABLE_NODE(type)*)calloc(1, sizeof(LINEAR_HASHTABLE_NODE(type))); \
    srand(time(0)); \
    lt->z=rand()|0x1;   \
    lt->q=0;    \
    lt->n=0;    \
}   \
unsigned int LINEAR_HASHTABLE_HASH(type)(LINEAR_HASHTABLE(type)* lt, type x) { \
    return ((uint64_t)lt->z*x)>>(32-lt->d)&((1ul<<lt->d)-1); \
}   \
void LINEAR_HASHTABLE_RESIZE(type)(LINEAR_HASHTABLE(type)* lt) {    \
    unsigned int d=1;   \
    while((1ul<<d)<lt->n*3) \
        d++;    \
    unsigned int cap=1ul<<lt->d;    \
    lt->d=d;    \
    unsigned int new_cap=1ul<<lt->d;    \
    LINEAR_HASHTABLE_NODE(type)* new_t=(LINEAR_HASHTABLE_NODE(type)*)calloc(1ul<<d, sizeof(LINEAR_HASHTABLE_NODE(type)));  \
    for(int i=0; i<cap; i++) {  \
        if(lt->t[i].t==LINEAR_HASHTABLE_DATA_NODE) {    \
            unsigned idx=LINEAR_HASHTABLE_HASH(type)(lt, lt->t[i].v);    \
            while(new_t[idx].t!=LINEAR_HASHTABLE_NULL_NODE) \
                idx=(idx+1)%new_cap;    \
            new_t[idx].t=LINEAR_HASHTABLE_DATA_NODE;    \
            new_t[idx].v=lt->t[i].v;    \
        }   \
    }   \
    lt->q=lt->n;    \
    free(lt->t);    \
    lt->t=new_t;    \
}   \
bool LINEAR_HASHTABLE_FIND(type)(LINEAR_HASHTABLE(type)* lt, type val) { \
    unsigned int idx=LINEAR_HASHTABLE_HASH(type)(lt, val);  \
    unsigned int cap=1ul<<lt->d;    \
    while(lt->t[idx].t!=LINEAR_HASHTABLE_NULL_NODE) {   \
        if(lt->t[idx].t!=LINEAR_HASHTABLE_DEL_NODE && lt->t[idx].v==val)   \
            return true;    \
        idx=(idx+1)%cap;    \
    }   \
    return false;   \
}   \
bool LINEAR_HASHTABLE_ADD(type)(LINEAR_HASHTABLE(type)* lt, type val) { \
    if(2*lt->q>lt->n)   \
        LINEAR_HASHTABLE_RESIZE(type)(lt);  \
    unsigned int idx=LINEAR_HASHTABLE_HASH(type)(lt, val);  \
    unsigned int cap=1ul<<lt->d;    \
    bool del_f=false;   \
    unsigned int del_idx=idx;   \
    while(lt->t[idx].t!=LINEAR_HASHTABLE_NULL_NODE) {   \
        if(lt->t[idx].t==LINEAR_HASHTABLE_DATA_NODE && lt->t[idx].v==val)   \
            return false;    \
        if(!del_f && lt->t[idx].t==LINEAR_HASHTABLE_DEL_NODE) { \
            del_f=true; \
            del_idx=idx;    \
        }   \
        idx=(idx+1)%cap;    \
    }   \
    idx=del_f?del_idx:idx;  \
    lt->q=del_f?lt->q:lt->q+1;  \
    lt->t[idx].t=LINEAR_HASHTABLE_DATA_NODE;    \
    lt->t[idx].v=val;   \
    lt->n+=1;   \
    return true;    \
}   \
bool LINEAR_HASHTABLE_REMOVE(type)(LINEAR_HASHTABLE(type)* lt, type val) { \
    unsigned int idx=LINEAR_HASHTABLE_HASH(type)(lt, val);  \
    unsigned int cap=1ul<<lt->d;    \
    while(lt->t[idx].t!=LINEAR_HASHTABLE_NULL_NODE) {   \
        if(lt->t[idx].t==LINEAR_HASHTABLE_DATA_NODE && lt->t[idx].v==val) { \
            lt->q+=1;   \
            lt->n-=1;   \
            lt->t[idx].t=LINEAR_HASHTABLE_DEL_NODE; \
            unsigned int cap=1ul<<lt->d;    \
            if(lt->n*8<cap) \
                LINEAR_HASHTABLE_RESIZE(type)(lt);  \
            return true;    \
        }   \
        idx=(idx+1)%cap;    \
    }   \
    return false;    \
}   \
void LINEAR_HASHTABLE_FREE(type)(LINEAR_HASHTABLE(type)* lt) {  \
    lt->d=0;    \
    free(lt->t);    \
    lt->t=NULL;  \
    lt->z=0;    \
    lt->q=0;    \
    lt->n=0;    \
}   \


void linear_hashtable_test();

#endif