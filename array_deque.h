#ifndef ARRAY_DEQUE_H
#define ARRAY_DEQUE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_DEQUE_CONCAT(X, Y)    X##_##Y##_
#define ARRAY_DEQUE(type)   ARRAY_DEQUE_CONCAT(array_deque, type)
#define ARRAY_DEQUE_INIT(type)  ARRAY_DEQUE_CONCAT(array_deque_init, type)
#define ARRAY_DEQUE_SIZE(type)  ARRAY_DEQUE_CONCAT(array_deque_size, type)
#define ARRAY_DEQUE_GET(type)   ARRAY_DEQUE_CONCAT(array_deque_get, type)
#define ARRAY_DEQUE_SET(type)   ARRAY_DEQUE_CONCAT(array_deque_set, type)
#define ARRAY_DEQUE_ADD(type)   ARRAY_DEQUE_CONCAT(array_deque_add, type)
#define ARRAY_DEQUE_REMOVE(type)   ARRAY_DEQUE_CONCAT(array_deque_remove, type)
#define ARRAY_DEQUE_PUSH_BACK(type)   ARRAY_DEQUE_CONCAT(array_deque_push_back, type)
#define ARRAY_DEQUE_POP_BACK(type)   ARRAY_DEQUE_CONCAT(array_deque_pop_back, type)
#define ARRAY_DEQUE_PUSH_FRONT(type)   ARRAY_DEQUE_CONCAT(array_deque_push_front, type)
#define ARRAY_DEQUE_POP_FRONT(type)   ARRAY_DEQUE_CONCAT(array_deque_pop_front, type)
#define ARRAY_DEQUE_RESIZE(type)    ARRAY_DEQUE_CONCAT(array_deque_resize, type)

#define ARRAY_DEQUE_INIT_CAP    1
#define ARRAY_DEQUE_DECL(type)  \
typedef struct ARRAY_DEQUE(type) {  \
    type* data; \
    unsigned int cap;   \
    unsigned int sta;   \
    unsigned int len;   \
} ARRAY_DEQUE(type);    \
void ARRAY_DEQUE_INIT(type)(ARRAY_DEQUE(type)* s) { \
    s->data=NULL;   \
    s->cap=0;   \
    s->sta=0;   \
    s->len=0;   \
}   \
unsigned int ARRAY_DEQUE_SIZE(type)(ARRAY_DEQUE(type)* s) { \
    return s->len;  \
}   \
type ARRAY_DEQUE_GET(type)(ARRAY_DEQUE(type)* s, unsigned int idx) {    \
    assert(idx<s->len); \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    return s->data[idx_];    \
}   \
type ARRAY_DEQUE_SET(type)(ARRAY_DEQUE(type)* s, unsigned int idx, type val) {  \
    assert(idx<s->len);    \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    type ret=s->data[idx_];  \
    s->data[idx_]=val;   \
    return ret; \
}   \
void ARRAY_DEQUE_RESIZE(type)(ARRAY_DEQUE(type)* s) {   \
    if(!s->len) {   \
        if(s->cap) {    \
            free(s->data);  \
            s->data=NULL;   \
            s->cap=0;   \
        }   \
        else {  \
            s->data=(type*)malloc(sizeof(type)*ARRAY_DEQUE_INIT_CAP);   \
            s->cap=ARRAY_DEQUE_INIT_CAP;    \
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
void ARRAY_DEQUE_ADD(type)(ARRAY_DEQUE(type)* s, unsigned int idx, type val) {  \
    assert(idx<=s->len);    \
    if(s->len==s->cap)  \
        ARRAY_DEQUE_RESIZE(type)(s);    \
    if(idx<s->len/2) {  \
        s->sta=(s->sta+s->cap-1)%s->cap;    \
        unsigned int idx_=(idx+s->sta)%s->cap;   \
        if(s->sta>=0) {   \
            memcpy(s->data+s->sta, s->data+s->sta+1, sizeof(type)*idx);   \
        }   \
        else {  \
            type tmp=s->data[0]; \
            memcpy(s->data, s->data+1, sizeof(type)*idx_);  \
            memcpy(s->data+s->sta, s->data+s->sta+1, sizeof(type)*(s->cap-1-s->sta));   \
            s->data[s->cap-1]=tmp; \
        }   \
        s->data[idx_]=val;   \
    }   \
    else {  \
        unsigned int idx_=(idx+s->sta)%s->cap;   \
        if(idx_+s->len-idx<s->cap) {   \
            memcpy(s->data+idx_+1, s->data+idx_, sizeof(type)*(s->len-idx));   \
        }   \
        else {  \
            unsigned int end=(s->sta+s->len)%s->cap;    \
            type tmp=s->data[s->cap-1]; \
            memcpy(s->data+idx_+1, s->data+idx_, sizeof(type)*(s->cap-idx_-1));  \
            memcpy(s->data+1, s->data, sizeof(type)*end);   \
            s->data[0]=tmp; \
        }   \
        s->data[idx_]=val;   \
    }   \
    s->len++;   \
}   \
type ARRAY_DEQUE_REMOVE(type)(ARRAY_DEQUE(type)* s, unsigned int idx) { \
    assert(idx<s->len); \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    type ret=s->data[idx_];  \
    if(idx<s->len/2) {  \
        if(idx_-idx>=0) {   \
            memcpy(s->data+s->sta+1, s->data+s->sta, sizeof(type)*idx);   \
        }   \
        else {  \
            type tmp=s->data[s->cap-1];    \
            memcpy(s->data+s->sta+1, s->data+s->sta, sizeof(type)*(s->cap-s->sta-1));    \
            memcpy(s->data+1, s->data, sizeof(type)*idx_);   \
            s->data[0]=tmp;  \
        }   \
        s->sta=(s->sta+1)%s->cap;   \
    }   \
    else {  \
        if(idx_+s->len-idx-1<s->cap) {   \
            memcpy(s->data+idx_, s->data+idx_+1, sizeof(type)*(s->len-idx-1));   \
        }   \
        else {  \
            unsigned int last=(s->sta+s->len-1)%s->cap;    \
            type tmp=s->data[0];    \
            memcpy(s->data+idx_, s->data+idx_+1, sizeof(type)*(s->cap-idx_-1));    \
            memcpy(s->data, s->data+1, sizeof(type)*last);   \
            s->data[s->cap-1]=tmp;  \
        }   \
    }   \
    s->len--;   \
    if(s->cap>=s->len*3)    \
        ARRAY_DEQUE_RESIZE(type)(s);    \
    return ret; \
}   \
void ARRAY_DEQUE_PUSH_BACK(type)(ARRAY_DEQUE(type)* s, type val) {   \
    ARRAY_DEQUE_ADD(type)(s, s->len, val);  \
}   \
type ARRAY_DEQUE_POP_BACK(type)(ARRAY_DEQUE(type)* s) {  \
    return ARRAY_DEQUE_REMOVE(type)(s, s->len-1); \
}   \
type ARRAY_DEQUE_PUSH_FRONT(type)(ARRAY_DEQUE(type)* s, type val) {   \
    ARRAY_DEQUE_ADD(type)(s, 0, val);   \
}   \
type ARRAY_DEQUE_POP_FRONT(type)(ARRAY_DEQUE(type)* s) {  \
    return ARRAY_DEQUE_REMOVE(type)(s, 0); \
}


void array_deque_test();

#endif