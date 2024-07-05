#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_QUEUE_CONCAT(X, Y)    X##Y##_
#define ARRAY_QUEUE(type)   ARRAY_QUEUE_CONCAT(array_queue, type)
#define ARRAY_QUEUE_INIT(type)  ARRAY_QUEUE_CONCAT(array_queue_init, type)
#define ARRAY_QUEUE_SIZE(type)  ARRAY_QUEUE_CONCAT(array_queue_size, type)
#define ARRAY_QUEUE_GET(type)   ARRAY_QUEUE_CONCAT(array_queue_get, type)
#define ARRAY_QUEUE_SET(type)   ARRAY_QUEUE_CONCAT(array_queue_set, type)
#define ARRAY_QUEUE_ADD(type)   ARRAY_QUEUE_CONCAT(array_queue_add, type)
#define ARRAY_QUEUE_REMOVE(type)   ARRAY_QUEUE_CONCAT(array_queue_remove, type)
#define ARRAY_QUEUE_PUSH_END(type)   ARRAY_QUEUE_CONCAT(array_queue_push, type)
#define ARRAY_QUEUE_POP_FRONT(type)   ARRAY_QUEUE_CONCAT(array_queue_pop, type)
#define ARRAY_QUEUE_RESIZE(type)    ARRAY_QUEUE_CONCAT(array_queue_resize, type)

#define ARRAY_QUEUE_INIT_CAP    1
#define ARRAY_QUEUE_DECL(type)  \
typedef struct ARRAY_QUEUE(type) {  \
    type* data; \
    unsigned int cap;   \
    unsigned int sta;   \
    unsigned int len;   \
} ARRAY_QUEUE(type);    \
void ARRAY_QUEUE_INIT(type)(ARRAY_QUEUE(type)* s) { \
    s->data=(type*)malloc(sizeof(type)*ARRAY_QUEUE_INIT_CAP);   \
    s->cap=1;   \
    s->sta=0;   \
    s->len=0;   \
}   \
unsigned int ARRAY_QUEUE_SIZE(type)(ARRAY_QUEUE(type)* s) { \
    return s->len;  \
}   \
type ARRAY_QUEUE_GET(type)(ARRAY_QUEUE(type)* s, unsigned int idx) {    \
    assert(idx<s->len); \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    return s->data[idx_];    \
}   \
type ARRAY_QUEUE_SET(type)(ARRAY_QUEUE(type)* s, unsigned int idx, type val) {  \
    assert(idx<s->len);    \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    type ret=s->data[idx_];  \
    s->data[idx_]=val;   \
    return ret; \
}   \
void ARRAY_QUEUE_RESIZE(type)(ARRAY_QUEUE(type)* s) {   \
    type* new_data=(type*)malloc(sizeof(type)*s->len*2);    \
    unsigned int end=(s->sta+s->len)%s->cap;    \
    if(s->sta<end || end==0) {    \
        memcpy(new_data, s->data+s->sta, sizeof(type)*(s->len));   \
    }   \
    else {  \
        memcpy(new_data, s->data+s->sta, sizeof(type)*(s->cap-s->sta));    \
        memcpy(new_data+s->cap-s->sta, s->data, sizeof(type)*end);   \
    }   \
    free(s->data);  \
    s->data=new_data;   \
    s->cap=s->len*2;    \
    s->sta=0;   \
}   \
void ARRAY_QUEUE_ADD(type)(ARRAY_QUEUE(type)* s, unsigned int idx, type val) {  \
    assert(idx<=s->len);    \
    if(s->len==s->cap)  \
        ARRAY_QUEUE_RESIZE(type)(s);    \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    unsigned int end=(s->sta+s->len)%s->cap;    \
    if(idx_<=end) {   \
        memcpy(s->data+idx_+1, s->data+idx_, sizeof(type)*(end-idx_));   \
    }   \
    else {  \
        type tmp=s->data[s->cap-1]; \
        memcpy(s->data+idx_+1, s->data+idx_, sizeof(type)*(s->cap-idx_));  \
        if(end>0)   \
            memcpy(s->data+1, s->data, sizeof(type)*(end-1));   \
        s->data[0]=tmp; \
    }   \
    s->data[idx_]=val;   \
    s->len++;   \
}   \
type ARRAY_QUEUE_REMOVE(type)(ARRAY_QUEUE(type)* s, unsigned int idx) { \
    assert(idx<s->len); \
    type ret=s->data[idx];  \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    unsigned int end=(s->sta+s->len)%s->cap;    \
    if(idx_<end) {   \
        memcpy(s->data+idx_, s->data+idx_+1, sizeof(type)*(end-idx_-1));   \
    }   \
    else {  \
        type tmp=s->data[0];    \
        memcpy(s->data+idx_, s->data+idx_+1, sizeof(type)*(s->cap)-idx_-1);    \
        if(end>0)   \
            memcpy(s->data, s->data+1, sizeof(type)*(end-1));   \
        s->data[s->cap-1]=tmp;  \
    }   \
    s->len--;   \
    if(s->cap>=s->len*3)    \
        ARRAY_QUEUE_RESIZE(type)(s);    \
    return ret; \
}   \
void ARRAY_QUEUE_PUSH_END(type)(ARRAY_QUEUE(type)* s, type val) {   \
    ARRAY_QUEUE_ADD(type)(s, s->len, val);  \
}   \
type ARRAY_QUEUE_POP_FRONT(type)(ARRAY_QUEUE(type)* s) {  \
    return ARRAY_QUEUE_REMOVE(type)(s, 0); \
}



void array_queue_test();

#endif