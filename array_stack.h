#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_STACK_CONCAT(X, Y)    X##_##Y##_
#define ARRAY_STACK(type)   ARRAY_STACK_CONCAT(array_stack, type)
#define ARRAY_STACK_INIT(type)  ARRAY_STACK_CONCAT(array_stack_init, type)
#define ARRAY_STACK_SIZE(type)  ARRAY_STACK_CONCAT(array_stack_size, type)
#define ARRAY_STACK_GET(type)   ARRAY_STACK_CONCAT(array_stack_get, type)
#define ARRAY_STACK_SET(type)   ARRAY_STACK_CONCAT(array_stack_set, type)
#define ARRAY_STACK_ADD(type)   ARRAY_STACK_CONCAT(array_stack_add, type)
#define ARRAY_STACK_REMOVE(type)   ARRAY_STACK_CONCAT(array_stack_remove, type)
#define ARRAY_STACK_PUSH(type)   ARRAY_STACK_CONCAT(array_stack_push, type)
#define ARRAY_STACK_POP(type)   ARRAY_STACK_CONCAT(array_stack_pop, type)
#define ARRAY_STACK_RESIZE(type)    ARRAY_STACK_CONCAT(array_stack_resize, type)

#define ARRAY_STACK_INIT_CAP    1
#define ARRAY_STACK_DECL(type)  \
typedef struct ARRAY_STACK(type) {  \
    type* data; \
    unsigned int cap;   \
    unsigned int len;   \
} ARRAY_STACK(type);    \
void ARRAY_STACK_INIT(type)(ARRAY_STACK(type)* s) { \
    s->data=NULL;   \
    s->cap=0;   \
    s->len=0;   \
}   \
unsigned int ARRAY_STACK_SIZE(type)(ARRAY_STACK(type)* s) {   \
    return s->len;  \
}   \
type ARRAY_STACK_GET(type)(ARRAY_STACK(type)* s, unsigned int idx) {    \
    assert(idx<s->len); \
    return s->data[idx];    \
}   \
type ARRAY_STACK_SET(type)(ARRAY_STACK(type)* s, unsigned int idx, type val) {  \
    assert(idx<s->len);    \
    type ret=s->data[idx];  \
    s->data[idx]=val;   \
    return ret; \
}   \
void ARRAY_STACK_RESIZE(type)(ARRAY_STACK(type)* s) {   \
    if(!s->len) {   \
        if(s->cap) {    \
            free(s->data);  \
            s->data=NULL;   \
            s->cap=0;   \
        }   \
        else {  \
            s->data=(type*)malloc(sizeof(type)*ARRAY_STACK_INIT_CAP);   \
            s->cap=ARRAY_STACK_INIT_CAP;    \
        }   \
        return; \
    }   \
    type* new_data=(type*)malloc(sizeof(type)*s->len*2);    \
    memcpy(new_data, s->data, sizeof(type)*(s->len));  \
    free(s->data);  \
    s->data=new_data;   \
    s->cap=s->len*2;    \
}   \
void ARRAY_STACK_ADD(type)(ARRAY_STACK(type)* s, unsigned int idx, type val) {  \
    assert(idx<=s->len);    \
    if(s->len==s->cap)  \
        ARRAY_STACK_RESIZE(type)(s);    \
    memcpy(s->data+idx+1, s->data+idx, sizeof(type)*(s->len-idx)); \
    s->data[idx]=val;   \
    s->len++;   \
}   \
type ARRAY_STACK_REMOVE(type)(ARRAY_STACK(type)* s, unsigned int idx) { \
    assert(idx<s->len); \
    type ret=s->data[idx];  \
    memcpy(s->data+idx, s->data+idx+1, sizeof(type)*(s->len-idx-1));   \
    s->len--;   \
    if(s->cap>=s->len*3)    \
        ARRAY_STACK_RESIZE(type)(s);    \
    return ret; \
}   \
void ARRAY_STACK_PUSH(type)(ARRAY_STACK(type)* s, type val) {   \
    ARRAY_STACK_ADD(type)(s, s->len, val);  \
}   \
type ARRAY_STACK_POP(type)(ARRAY_STACK(type)* s) {  \
    return ARRAY_STACK_REMOVE(type)(s, s->len-1); \
}   \


void array_stack_test();

#endif