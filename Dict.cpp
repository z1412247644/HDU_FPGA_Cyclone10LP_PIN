//
// Created by lenovo on 2018-10-11.
//

#include "Dict.h"
#include "cstdlib"
My_Status InitDict(Dictptr &d) {
    d = (Dictptr) malloc(sizeof(Dict));
    d->next = nullptr;
    return OK;
}
/*
My_Status AddDict(Dictptr & d, int key, DElemType value){
    Dictptr p=(Dictptr)malloc(sizeof(Dict)), q=d;
    p->data.key = key;
    p->data.value = value;
    p->next = NULL;
    while (q->next!=NULL)
        q = q->next;
    q->next = p;
    return OK;
}
*/
My_Status FindDictBy_key(Dictptr &d, DNode &e, int key) {
    Dictptr p = d->next;
    while (p != nullptr && p->data.key != key) p = p->next;
    if (p == nullptr) return ERROR;
    e = p->data;
    return OK;
}

My_Status AddDict(Dictptr &d, int key, DElemType value) {
    Dictptr ptr = d;
    while (ptr->next != nullptr && ptr->next->data.key != key) ptr = ptr->next;
    if (ptr->next == nullptr) {
        Dictptr p = (Dictptr) malloc(sizeof(Dict));
        p->data.key = key;
        p->data.value = value;
        p->next = nullptr;
        ptr->next = p;
        return OK;
    }
    ptr->next->data.value = value;
    return OK;
}

My_Status DestroyDict(Dictptr &d) {
    Dictptr ptr = d;
    while (d != nullptr) {
        ptr = d->next;
        free(d);
        d = ptr;
    }
    return OK;
}
