#ifndef WJH_DICT_H
#define WJH_DICT_H
#include<QString>
#define DElemType QString
#define KElemType QString
#define My_Status int
#define OK 0
#define ERROR 1

typedef struct DNode {
     KElemType key;
    DElemType value;

} DNode;

typedef struct Dict {
    DNode data;
    struct Dict *next;
} Dict, *Dictptr;

My_Status InitDict(Dictptr &d);

My_Status AddDict(Dictptr &d, KElemType key, DElemType value);

My_Status FindDictBy_key(Dictptr &d, DNode &e, KElemType key);

My_Status DestroyDict(Dictptr &d);

#endif //WJH_DICT_H
