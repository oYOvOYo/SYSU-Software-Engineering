
#if 0        

#ifndef STACK_S_MACRO_H_
#define STACK_S_MACRO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h> // for malloc, free

typedef struct {
    void *top;
    void *bottom;
} Stack_s;

#define initStack(P, TYPE, SIZE) \
    do {\
        (P).top = (P).bottom = malloc((SIZE) * sizeof(TYPE));\
    } while (0)

#define destroyStack(P) \
    do {\
        free((P).bottom);\
    } while (0)

#define sizeStack(P, TYPE) \
    ((size_t)(((TYPE*)(P).top) - ((TYPE*)(P).bottom)))

#define emptyStack(P) \
    ((P).top == (P).bottom)

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

#ifdef __cplusplus
}
#endif

#endif // STACK_S_MACRO_H_


#else


#include <stdlib.h> //for malloc free


typedef struct{
     void* now;
     void* end;
} Stack_s;

#define initStack(p, type, size) \
    do{\                                         
        (p).now = (p).end = malloc(sizeof(type) * size);\
    }while(0) 
  
#define pushStack(p, type, value) \
    do{\
        
        (*(type*)(p).now) = value;\
                 ((type*)(p).now)++;\
    }while(0)

#define peekStack(p, type)　\
     *(((type*)((p).now))-1)

#define popStack(p, type)　\
         (((type*)((p).now))--)

#define emptyStack(p) \
        (p.now == p.end)

#define sizeStack(p, type) \
        p.now - p.end 



#endif