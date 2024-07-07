#ifndef SPACE_EFFICIENT_LINKED_LIST_FIXED_H
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(X, Y)    X##_##Y##_
#define SPACE_EFFICIENT_LINKED_LIST_FIXED(type)   SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_INIT(type)  SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_init, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)  SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_size, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_GET(type)   SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_get, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_SET(type)   SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_set, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_ADD(type)   SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_add, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_REMOVE(type)   SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_remove, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_PUSH_BACK(type)   SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_push_back, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_POP_BACK(type)   SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_pop_back, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_PUSH_FRONT(type)   SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_push_front, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_POP_FRONT(type)   SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_pop_front, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIXED_FREE(type)    SPACE_EFFICIENT_LINKED_LIST_FIXED_CONCAT(space_efficient_linked_list_fixed_free, type)

#define SPACE_EFFICIENT_LINKED_LIST_FIXED_DECL(type)  \
typedef struct SPACE_EFFICIENT_LINKED_LIST_FIXED(type) {  \
    type* data; \
    unsigned int cap;   \
    unsigned int sta;   \
    unsigned int len;   \
} SPACE_EFFICIENT_LINKED_LIST_FIXED(type);    \
void SPACE_EFFICIENT_LINKED_LIST_FIXED_INIT(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s, unsigned int fix_size) { \
    s->data=(type*)malloc(sizeof(type)*fix_size);   \
    s->cap=fix_size;   \
    s->sta=0;   \
    s->len=0;   \
}   \
unsigned int SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s) { \
    return s->len;  \
}   \
type SPACE_EFFICIENT_LINKED_LIST_FIXED_GET(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s, unsigned int idx) {    \
    assert(idx<s->len); \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    return s->data[idx_];    \
}   \
type SPACE_EFFICIENT_LINKED_LIST_FIXED_SET(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s, unsigned int idx, type val) {  \
    assert(idx<s->len);    \
    unsigned int idx_=(idx+s->sta)%s->cap;   \
    type ret=s->data[idx_];  \
    s->data[idx_]=val;   \
    return ret; \
}   \
void SPACE_EFFICIENT_LINKED_LIST_FIXED_ADD(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s, unsigned int idx, type val) {  \
    assert(idx<=s->len);    \
    assert(s->len<s->cap);  \
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
type SPACE_EFFICIENT_LINKED_LIST_FIXED_REMOVE(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s, unsigned int idx) { \
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
    return ret; \
}   \
void SPACE_EFFICIENT_LINKED_LIST_FIXED_PUSH_BACK(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s, type val) {   \
    SPACE_EFFICIENT_LINKED_LIST_FIXED_ADD(type)(s, s->len, val);  \
}   \
type SPACE_EFFICIENT_LINKED_LIST_FIXED_POP_BACK(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s) {  \
    return SPACE_EFFICIENT_LINKED_LIST_FIXED_REMOVE(type)(s, s->len-1); \
}   \
type SPACE_EFFICIENT_LINKED_LIST_FIXED_PUSH_FRONT(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s, type val) {   \
    SPACE_EFFICIENT_LINKED_LIST_FIXED_ADD(type)(s, 0, val);   \
}   \
type SPACE_EFFICIENT_LINKED_LIST_FIXED_POP_FRONT(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s) {  \
    return SPACE_EFFICIENT_LINKED_LIST_FIXED_REMOVE(type)(s, 0); \
}   \
type SPACE_EFFICIENT_LINKED_LIST_FIXED_FREE(type)(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* s) {  \
    free(s->data);  \
    s->data=NULL;   \
    s->cap=0;   \
    s->sta=0;   \
    s->len=0;   \
}


#define SPACE_EFFICIENT_LINKED_LIST_CONCAT(X, Y)    X##_##Y##_
#define SPACE_EFFICIENT_LINKED_LIST_NODE(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_node, type)
#define SPACE_EFFICIENT_LINKED_LIST(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list, type)
#define SPACE_EFFICIENT_LINKED_LIST_INIT(type)  SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_init, type)
#define SPACE_EFFICIENT_LINKED_LIST_SIZE(type)  SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_size, type)
#define SPACE_EFFICIENT_LINKED_LIST_FIND(type)  SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_find, type)
#define SPACE_EFFICIENT_LINKED_LIST_GET(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_get, type)
#define SPACE_EFFICIENT_LINKED_LIST_SET(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_set, type)
#define SPACE_EFFICIENT_LINKED_LIST_ADD(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_add, type)
#define SPACE_EFFICIENT_LINKED_LIST_REMOVE(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_remove, type)
#define SPACE_EFFICIENT_LINKED_LIST_PUSH_BACK(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_push_back, type)
#define SPACE_EFFICIENT_LINKED_LIST_POP_BACK(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_pop_back, type)
#define SPACE_EFFICIENT_LINKED_LIST_PUSH_FRONT(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_push_front, type)
#define SPACE_EFFICIENT_LINKED_LIST_POP_FRONT(type)   SPACE_EFFICIENT_LINKED_LIST_CONCAT(space_efficient_linked_list_pop_front, type)

#define SPACE_EFFICIENT_LINKED_LIST_DECL(type)  \
typedef struct SPACE_EFFICIENT_LINKED_LIST_NODE(type) { \
    SPACE_EFFICIENT_LINKED_LIST_FIXED(type)* d; \
    struct SPACE_EFFICIENT_LINKED_LIST_NODE(type)* next;    \
    struct SPACE_EFFICIENT_LINKED_LIST_NODE(type)* pre; \
} SPACE_EFFICIENT_LINKED_LIST_NODE(type);   \
typedef struct SPACE_EFFICIENT_LINKED_LIST(type) {  \
    SPACE_EFFICIENT_LINKED_LIST_NODE(type) dummy;    \
    unsigned int b; \
    unsigned int len;   \
} SPACE_EFFICIENT_LINKED_LIST(type);    \
void SPACE_EFFICIENT_LINKED_LIST_INIT(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel, unsigned int size) {   \
    assert(size>0); \
    sel->dummy.next=&sel->dummy;    \
    sel->dummy.pre=&sel->dummy; \
    sel->b=size;   \
    sel->len=0; \
}   \
unsigned int SPACE_EFFICIENT_LINKED_LIST_SIZE(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel) {   \
    return sel->len;    \
}   \
SPACE_EFFICIENT_LINKED_LIST_NODE(type)* SPACE_EFFICIENT_LINKED_LIST_FIND(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel, unsigned int idx, unsigned int* out_idx) {   \
    SPACE_EFFICIENT_LINKED_LIST_NODE(type)* ret=NULL;   \
    if(idx<sel->len/2) {    \
        ret=sel->dummy.next;    \
        while(idx>=SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(ret->d)) {  \
            idx-=SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(ret->d); \
            ret=ret->next;  \
        }   \
    }   \
    else {  \
        ret=&sel->dummy; \
        unsigned int n=sel->len;    \
        while(idx<n) {  \
            ret=ret->pre;   \
            n-=SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(ret->d);   \
        }   \
        idx=idx-n;  \
    }   \
    *out_idx=idx;   \
    return ret; \
}   \
type SPACE_EFFICIENT_LINKED_LIST_GET(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel, unsigned int idx) {    \
    assert(idx<sel->len);   \
    unsigned int idx_=0;    \
    SPACE_EFFICIENT_LINKED_LIST_NODE(type)* node=SPACE_EFFICIENT_LINKED_LIST_FIND(type)(sel, idx, &idx_); \
    return SPACE_EFFICIENT_LINKED_LIST_FIXED_GET(type)(node->d, idx_);  \
}   \
type SPACE_EFFICIENT_LINKED_LIST_SET(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel, unsigned int idx, type val) {    \
    assert(idx<sel->len);   \
    unsigned int idx_=0;    \
    SPACE_EFFICIENT_LINKED_LIST_NODE(type)* node=SPACE_EFFICIENT_LINKED_LIST_FIND(type)(sel, idx, &idx_); \
    type ret=SPACE_EFFICIENT_LINKED_LIST_FIXED_SET(type)(node->d, idx_, val);   \
    return ret; \
}   \
void SPACE_EFFICIENT_LINKED_LIST_ADD(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel, unsigned int idx, type val) { \
    assert(idx<=sel->len);  \
    unsigned int idx_=0;    \
    SPACE_EFFICIENT_LINKED_LIST_NODE(type)* u=SPACE_EFFICIENT_LINKED_LIST_FIND(type)(sel, idx, &idx_); \
    unsigned int r=0;   \
    SPACE_EFFICIENT_LINKED_LIST_NODE(type)* w=u;    \
    while(r<sel->b && w!=&sel->dummy && SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(w->d)==sel->b+1) {  \
        w=w->next;  \
        r++;    \
    }   \
    if(r==sel->b) {  \
        SPACE_EFFICIENT_LINKED_LIST_NODE(type)* node=(SPACE_EFFICIENT_LINKED_LIST_NODE(type)*)malloc(sizeof(SPACE_EFFICIENT_LINKED_LIST_NODE(type)));  \
        node->d=(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)*)malloc(sizeof(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)));  \
        SPACE_EFFICIENT_LINKED_LIST_FIXED_INIT(type)(node->d, sel->b+1);    \
        node->next=w;  \
        node->pre=w->pre;   \
        node->pre->next=node;   \
        node->next->pre=node;   \
        w=node; \
        while(w!=u) {   \
            while(SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(w->d)<sel->b) { \
                SPACE_EFFICIENT_LINKED_LIST_FIXED_PUSH_FRONT(type)(w->d, SPACE_EFFICIENT_LINKED_LIST_FIXED_POP_BACK(type)(w->pre->d));  \
            }   \
            w=w->pre;   \
        }   \
    }   \
    else if(w==&sel->dummy) {    \
        SPACE_EFFICIENT_LINKED_LIST_NODE(type)* node=(SPACE_EFFICIENT_LINKED_LIST_NODE(type)*)malloc(sizeof(SPACE_EFFICIENT_LINKED_LIST_NODE(type)));  \
        node->d=(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)*)malloc(sizeof(SPACE_EFFICIENT_LINKED_LIST_FIXED(type)));  \
        SPACE_EFFICIENT_LINKED_LIST_FIXED_INIT(type)(node->d, sel->b+1);    \
        node->next=&sel->dummy;  \
        node->pre=sel->dummy.pre;   \
        node->pre->next=node;   \
        node->next->pre=node;   \
        w=node;    \
        if(u==&sel->dummy)  \
            u=w;    \
    }   \
    while(w!=u) {   \
        SPACE_EFFICIENT_LINKED_LIST_FIXED_PUSH_FRONT(type)(w->d, SPACE_EFFICIENT_LINKED_LIST_FIXED_POP_BACK(type)(w->pre->d));  \
        w=w->pre;   \
    }   \
    SPACE_EFFICIENT_LINKED_LIST_FIXED_ADD(type)(w->d, idx_, val);  \
    sel->len++; \
}   \
type SPACE_EFFICIENT_LINKED_LIST_REMOVE(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel, unsigned int idx) { \
    assert(idx<sel->len);  \
    unsigned int idx_=0;    \
    SPACE_EFFICIENT_LINKED_LIST_NODE(type)* u=SPACE_EFFICIENT_LINKED_LIST_FIND(type)(sel, idx, &idx_);    \
    unsigned int r=0;   \
    SPACE_EFFICIENT_LINKED_LIST_NODE(type)* w=u;    \
    while(r<sel->b && w!=&sel->dummy && SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(w->d)==sel->b-1) { \
        w=w->next;  \
        r++;    \
    }   \
    if(r==sel->b) {  \
        w=w->pre;   \
        while(w!=u) {   \
            while(SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(w->d)<sel->b) {   \
                SPACE_EFFICIENT_LINKED_LIST_FIXED_PUSH_FRONT(type)(w->d, SPACE_EFFICIENT_LINKED_LIST_FIXED_POP_BACK(type)(w->pre->d));   \
            }   \
            w=w->pre;   \
        }   \
        assert(!SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(w->d));   \
        w->next->pre=w->pre;    \
        w=w->next;  \
        SPACE_EFFICIENT_LINKED_LIST_FIXED_FREE(type)(w->pre->next->d);    \
        free(w->pre->next); \
        w->pre->next=w; \
        u=w;    \
    }   \
    type ret=SPACE_EFFICIENT_LINKED_LIST_FIXED_REMOVE(type)(u->d, idx_);   \
    while(u!=w && u->next!=&sel->dummy) {   \
        SPACE_EFFICIENT_LINKED_LIST_FIXED_PUSH_BACK(type)(u->d, SPACE_EFFICIENT_LINKED_LIST_FIXED_POP_FRONT(type)(u->next->d));   \
        u=u->next;  \
    }   \
    if(!SPACE_EFFICIENT_LINKED_LIST_FIXED_SIZE(type)(u->d)) { \
        u->next->pre=u->pre;    \
        u=u->next;  \
        SPACE_EFFICIENT_LINKED_LIST_FIXED_FREE(type)(u->pre->next->d);    \
        free(u->pre->next); \
        u->pre->next=u; \
    }   \
    sel->len--; \
    return ret; \
}   \
void SPACE_EFFICIENT_LINKED_LIST_PUSH_BACK(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel, type val) {    \
    SPACE_EFFICIENT_LINKED_LIST_ADD(type)(sel, sel->len, val);    \
}   \
type SPACE_EFFICIENT_LINKED_LIST_POP_BACK(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel) {    \
    return SPACE_EFFICIENT_LINKED_LIST_REMOVE(type)(sel, sel->len-1);    \
}   \
void SPACE_EFFICIENT_LINKED_LIST_PUSH_FRONT(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel, type val) {    \
    SPACE_EFFICIENT_LINKED_LIST_ADD(type)(sel, 0, val);    \
}   \
type SPACE_EFFICIENT_LINKED_LIST_POP_FRONT(type)(SPACE_EFFICIENT_LINKED_LIST(type)* sel) {    \
    return SPACE_EFFICIENT_LINKED_LIST_REMOVE(type)(sel, 0);    \
}


void space_efficient_linked_list_test();

#endif