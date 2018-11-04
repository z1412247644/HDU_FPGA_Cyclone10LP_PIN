#ifndef WJH_DICT_H
#define WJH_DICT_H

#define DElemType bool
#define My_Status int
#define OK 0
#define ERROR 1

typedef struct DNode {
    int key;
    DElemType value;

} DNode;

typedef struct Dict {
    DNode data;
    struct Dict *next;
} Dict, *Dictptr;

My_Status InitDict(Dictptr &d);

My_Status AddDict(Dictptr &d, int key, DElemType value);

My_Status FindDictBy_key(Dictptr &d, DNode &e, int key);

My_Status DestroyDict(Dictptr &d);

#endif //WJH_DICT_H
