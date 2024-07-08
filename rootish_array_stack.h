#ifndef ARRAY_ROOTISH_ARRAY_STACK_H
#define ARRAY_ROOTISH_ARRAY_STACK_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ARRAY_QUEUE_FIXED_CONCAT(X, Y)    X##_##Y##_
#define ARRAY_QUEUE_FIXED(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed, type)
#define ARRAY_QUEUE_FIXED_INIT(type)  ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_init, type)
#define ARRAY_QUEUE_FIXED_SIZE(type)  ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_size, type)
#define ARRAY_QUEUE_FIXED_GET(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_get, type)
#define ARRAY_QUEUE_FIXED_SET(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_set, type)
#define ARRAY_QUEUE_FIXED_ADD(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_add, type)
#define ARRAY_QUEUE_FIXED_REMOVE(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_remove, type)
#define ARRAY_QUEUE_FIXED_PUSH_END(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_push_end, type)
#define ARRAY_QUEUE_FIXED_PUSH_FRONT(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_push_front, type)
#define ARRAY_QUEUE_FIXED_POP_END(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_pop_end, type)
#define ARRAY_QUEUE_FIXED_POP_FRONT(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_pop_front, type)
#define ARRAY_QUEUE_FIXED_FREE(type)   ARRAY_QUEUE_FIXED_CONCAT(array_queue_fixed_free, type)

#define ARRAY_QUEUE_FIXED_INIT_CAP    1
#define ARRAY_QUEUE_FIXED_DECL(type)  \
typedef struct ARRAY_QUEUE_FIXED(type) {  \
    type* data; \
    unsigned int cap;   \
    unsigned int sta;   \
    unsigned int len;   \
} ARRAY_QUEUE_FIXED(type);    \
void ARRAY_QUEUE_FIXED_INIT(type)(ARRAY_QUEUE_FIXED(type)* s, unsigned int fix_size) { \
    s->data=(type*)malloc(sizeof(type)*fix_size);   \
    s->cap=fix_size;   \
    s->sta=0;   \
    s->len=0;   \
}   \
unsigned int ARRAY_QUEUE_FIXED_SIZE(type)(ARRAY_QUEUE_FIXED(type)* s) { \
    return s->len;  \
}   \
type ARRAY_QUEUE_FIXED_GET(type)(ARRAY_QUEUE_FIXED(type)* s, unsigned int idx) {    \
    assert(idx<s->len); \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    return s->data[idx_];    \
}   \
type ARRAY_QUEUE_FIXED_SET(type)(ARRAY_QUEUE_FIXED(type)* s, unsigned int idx, type val) {  \
    assert(idx<s->len);    \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    type ret=s->data[idx_];  \
    s->data[idx_]=val;   \
    return ret; \
}   \
void ARRAY_QUEUE_FIXED_ADD(type)(ARRAY_QUEUE_FIXED(type)* s, unsigned int idx, type val) {  \
    assert(idx<=s->len);    \
    assert(s->len<s->cap);  \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    if(idx_+s->len-idx<s->cap) {   \
        memcpy(s->data+idx_+1, s->data+idx_, sizeof(type)*(s->len-idx));   \
    }   \
    else {  \
        unsigned int end=(s->sta+s->len)%s->cap;    \
        type tmp=s->data[s->cap-1]; \
        memcpy(s->data+idx_+1, s->data+idx_, sizeof(type)*(s->cap-idx_-1));  \
        memcpy(s->data+1, s->data, sizeof(type)*end);    \
        s->data[0]=tmp; \
    }   \
    s->data[idx_]=val;   \
    s->len++;   \
}   \
type ARRAY_QUEUE_FIXED_REMOVE(type)(ARRAY_QUEUE_FIXED(type)* s, unsigned int idx) { \
    assert(idx<s->len); \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    type ret=s->data[idx_];  \
    if(idx_+s->len-idx-1<s->cap) {   \
        memcpy(s->data+idx_, s->data+idx_+1, sizeof(type)*(s->len-idx-1));   \
    }   \
    else {  \
        unsigned int last=(s->sta+s->len-1)%s->cap;    \
        type tmp=s->data[0];    \
        memcpy(s->data, s->data+1, sizeof(type)*last);   \
        memcpy(s->data+idx_, s->data+idx_+1, sizeof(type)*(s->cap-idx_-1));    \
        s->data[s->cap-1]=tmp;  \
    }   \
    s->len--;   \
    return ret; \
}   \
void ARRAY_QUEUE_FIXED_PUSH_END(type)(ARRAY_QUEUE_FIXED(type)* s, type val) {   \
    ARRAY_QUEUE_FIXED_ADD(type)(s, s->len, val);  \
}   \
void ARRAY_QUEUE_FIXED_PUSH_FRONT(type)(ARRAY_QUEUE_FIXED(type)* s, type val) {   \
    ARRAY_QUEUE_FIXED_ADD(type)(s, 0, val);  \
}   \
type ARRAY_QUEUE_FIXED_POP_END(type)(ARRAY_QUEUE_FIXED(type)* s) {  \
    return ARRAY_QUEUE_FIXED_REMOVE(type)(s, s->len-1); \
}   \
type ARRAY_QUEUE_FIXED_POP_FRONT(type)(ARRAY_QUEUE_FIXED(type)* s) {  \
    return ARRAY_QUEUE_FIXED_REMOVE(type)(s, 0); \
}   \
void ARRAY_QUEUE_FIXED_FREE(type)(ARRAY_QUEUE_FIXED(type)* s) {  \
    free(s->data);  \
    s->data=NULL;   \
    s->cap=0;   \
    s->sta=0;   \
    s->len=0;   \
}   \


#define ROOTISH_ARRAY_STACK_CONCAT(X, Y)    X##_##Y##_
#define ROOTISH_ARRAY_STACK(type)   ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack, type)
#define ROOTISH_ARRAY_STACK_INIT(type)  ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_init, type)
#define ROOTISH_ARRAY_STACK_SIZE(type)  ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_size, type)
#define ROOTISH_ARRAY_STACK_GET(type)   ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_get, type)
#define ROOTISH_ARRAY_STACK_SET(type)   ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_set, type)
#define ROOTISH_ARRAY_STACK_GROW(type)  ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_grow, type)
#define ROOTISH_ARRAY_STACK_SHRINK(type)    ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_shrink, type)
#define ROOTISH_ARRAY_STACK_ADD(type)   ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_add, type)
#define ROOTISH_ARRAY_STACK_REMOVE(type)   ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_remove, type)
#define ROOTISH_ARRAY_STACK_PUSH(type)   ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_push, type)
#define ROOTISH_ARRAY_STACK_POP(type)   ROOTISH_ARRAY_STACK_CONCAT(rootish_array_stack_pop, type)

#define I2B(idx)    (unsigned int)ceil((-3.0+sqrt(9+8*(idx)))/2)
#define SUM_BF(b)   ((b)*((b)+1))/2
#define ROOTISH_ARRAY_STACK_DECL(type)  \
ARRAY_QUEUE_FIXED_DECL(type) \
typedef struct ROOTISH_ARRAY_STACK(type) {  \
    ARRAY_QUEUE_FIXED(type)** blocks;    \
    unsigned int n; \
    unsigned int len;   \
} ROOTISH_ARRAY_STACK(type);    \
void ROOTISH_ARRAY_STACK_INIT(type)(ROOTISH_ARRAY_STACK(type)* s) { \
    s->blocks=NULL; \
    s->n=0; \
    s->len=0;   \
}   \
unsigned int ROOTISH_ARRAY_STACK_SIZE(type)(ROOTISH_ARRAY_STACK(type)* s) { \
    return s->len;  \
}   \
type ROOTISH_ARRAY_STACK_GET(type)(ROOTISH_ARRAY_STACK(type)* s, unsigned int idx) {    \
    assert(idx<s->len);    \
    unsigned int b=I2B(idx);    \
    unsigned int j=idx-SUM_BF(b); \
    return ARRAY_QUEUE_FIXED_GET(type)(s->blocks[b], j);  \
}   \
type ROOTISH_ARRAY_STACK_SET(type)(ROOTISH_ARRAY_STACK(type)* s, unsigned int idx, type val) {    \
    assert(idx<s->len);    \
    unsigned int b=I2B(idx);    \
    unsigned int j=idx-SUM_BF(b); \
    return ARRAY_QUEUE_FIXED_SET(type)(s->blocks[b], j, val);  \
}   \
void ROOTISH_ARRAY_STACK_GROW(type)(ROOTISH_ARRAY_STACK(type)* s) { \
    s->n+=1;    \
    s->blocks=(ARRAY_QUEUE_FIXED(type)**)realloc(s->blocks, sizeof(ARRAY_QUEUE_FIXED(type)*)*s->n); \
    s->blocks[s->n-1]=(ARRAY_QUEUE_FIXED(type)*)malloc(sizeof(ARRAY_QUEUE_FIXED(type))); \
    ARRAY_QUEUE_FIXED_INIT(type)(s->blocks[s->n-1], s->n);  \
}   \
void ROOTISH_ARRAY_STACK_SHRINK(type)(ROOTISH_ARRAY_STACK(type)* s) { \
    if(ARRAY_QUEUE_FIXED_SIZE(type)(s->blocks[s->n-1])==0) {  \
        ARRAY_QUEUE_FIXED_FREE(type)(s->blocks[s->n-1]);  \
        s->n-=1;    \
        s->blocks=(ARRAY_QUEUE_FIXED(type)**)realloc(s->blocks, sizeof(ARRAY_QUEUE_FIXED(type)*)*s->n);    \
    }   \
}   \
void ROOTISH_ARRAY_STACK_ADD(type)(ROOTISH_ARRAY_STACK(type)* s, unsigned int idx, type val) {  \
    assert(idx<=s->len);    \
    if(s->len==SUM_BF(s->n))  \
        ROOTISH_ARRAY_STACK_GROW(type)(s);   \
    unsigned int b=I2B(idx);    \
    unsigned int j=idx-SUM_BF(b); \
    for(int i=s->n-1; i>b; i--) { \
        ARRAY_QUEUE_FIXED_PUSH_FRONT(type)(s->blocks[i], ARRAY_QUEUE_FIXED_POP_END(type)(s->blocks[i-1]));    \
    }   \
    ARRAY_QUEUE_FIXED_ADD(type)(s->blocks[b], j, val);  \
    s->len+=1;  \
}   \
type ROOTISH_ARRAY_STACK_REMOVE(type)(ROOTISH_ARRAY_STACK(type)* s, unsigned int idx) { \
    assert(idx<s->len);    \
    unsigned int b=I2B(idx);    \
    unsigned int j=idx-SUM_BF(b); \
    type ret=ARRAY_QUEUE_FIXED_REMOVE(type)(s->blocks[b], j);  \
    for(int i=b; i<s->n-1; i++) {   \
        ARRAY_QUEUE_FIXED_PUSH_END(type)(s->blocks[i], ARRAY_QUEUE_FIXED_POP_FRONT(type)(s->blocks[i-1]));  \
    }   \
    s->len-=1;  \
    ROOTISH_ARRAY_STACK_SHRINK(type)(s);  \
    return ret; \
}   \
void ROOTISH_ARRAY_STACK_PUSH(type)(ROOTISH_ARRAY_STACK(type)* s, type val) {   \
    ROOTISH_ARRAY_STACK_ADD(type)(s, s->len, val);    \
}   \
type ROOTISH_ARRAY_STACK_POP(type)(ROOTISH_ARRAY_STACK(type)* s) {   \
    return ROOTISH_ARRAY_STACK_REMOVE(type)(s, s->len-1);    \
}   \



void rootish_array_stack_test();

#endif