#include "stdlib.h"

#ifndef STACK_S_H
#define STACK_S_H

typedef struct{
     void* top;
     void* bottom;
} Stack_s;

#define initStack(P, TYPE, SIZE) \
    do {\
        (P).top = (P).bottom = malloc(sizeof(TYPE) * (SIZE));\
    } while (0) 
  
#define destroyStack(P) \
    do {\
        free((p).bottom);\
    } while (0)

#define pushStack(P, TYPE, VALUE) \
    do {\
        TYPE* tmp = (P).top;\
        *tmp = (VALUE);\
        (P).top = (void*)(tmp + 1);\
    } while (0)

#define popStack(P, TYPE) \
    do {\
        TYPE* tmp = (P).top;\
        (P).top = (void*)(tmp - 1);\
    } while (0)

#define peekStack(P, TYPE) \
    (*(((TYPE*)((P).top)) - 1))


#define emptyStack(P) \
        ((P).top == (p).bottom)

#define sizeStack(P, TYPE) \
        ((size_t)(((TYPE*)(P).top) - ((TYPE*)(P).bottom)))


#endif


