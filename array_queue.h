#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_QUEUE_CONCAT(X, Y)    X##_##Y##_
#define ARRAY_QUEUE(type)   ARRAY_QUEUE_CONCAT(array_queue, type)
#define ARRAY_QUEUE_INIT(type)  ARRAY_QUEUE_CONCAT(array_queue_init, type)
#define ARRAY_QUEUE_SIZE(type)  ARRAY_QUEUE_CONCAT(array_queue_size, type)
#define ARRAY_QUEUE_GET(type)   ARRAY_QUEUE_CONCAT(array_queue_get, type)
#define ARRAY_QUEUE_SET(type)   ARRAY_QUEUE_CONCAT(array_queue_set, type)
#define ARRAY_QUEUE_ADD(type)   ARRAY_QUEUE_CONCAT(array_queue_add, type)
#define ARRAY_QUEUE_REMOVE(type)   ARRAY_QUEUE_CONCAT(array_queue_remove, type)
#define ARRAY_QUEUE_PUSH_BACK(type)   ARRAY_QUEUE_CONCAT(array_queue_push, type)
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
    s->data=NULL;   \
    s->cap=0;   \
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
    if(!s->len) {   \
        if(s->cap) {    \
            free(s->data);  \
            s->data=NULL;   \
            s->cap=0;   \
        }   \
        else {  \
            s->data=(type*)malloc(sizeof(type)*ARRAY_QUEUE_INIT_CAP);   \
            s->cap=ARRAY_QUEUE_INIT_CAP;    \
        }   \
        return; \
    }   \
    type* new_data=(type*)malloc(sizeof(type)*s->len*2);    \
    if(s->sta+s->len-1<s->cap) {    \
        memcpy(new_data, s->data+s->sta, sizeof(type)*(s->len));   \
    }   \
    else {  \
        unsigned int end=(s->sta+s->len)%s->cap;    \
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
type ARRAY_QUEUE_REMOVE(type)(ARRAY_QUEUE(type)* s, unsigned int idx) { \
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
    if(s->cap>=s->len*3)    \
        ARRAY_QUEUE_RESIZE(type)(s);    \
    return ret; \
}   \
void ARRAY_QUEUE_PUSH_BACK(type)(ARRAY_QUEUE(type)* s, type val) {   \
    ARRAY_QUEUE_ADD(type)(s, s->len, val);  \
}   \
type ARRAY_QUEUE_POP_FRONT(type)(ARRAY_QUEUE(type)* s) {  \
    return ARRAY_QUEUE_REMOVE(type)(s, 0); \
}



void array_queue_test();

#endif