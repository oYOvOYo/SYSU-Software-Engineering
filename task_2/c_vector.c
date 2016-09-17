// The implementation of the C vector in task 2.
// Copyright (c) 2016 sysu_AT. All righs reserved.

#include "c_vector.h"
#include "string.h" // for mammove
#include "stdlib.h" // for malloc, free 

/*-- Aux functions --*/

// Returns the largest of x and y.
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

// You can take the place of two functions below by memmove in <string.h>, or
// challenge yourself by the implementations of them.

// Copy the values of n bytes from the location pointed to by source (src)
//    directly to the memory block pointed to by destination (dst).
// It does support overlapping buffers, but it is only safe when dst > src, so
//    always do it backwards.
// For speedy copying, optimize the common case where both pointers and the
//    length are word-aligned, and copy word-at-a-time instead of
//    byte-at-a-time. Otherwise, copy by bytes. (Optional)
static inline void* memcpy_backward(void* dst, const void* src, size_t n) {
    /* size_t i;

    for (i = n-1; i >= 0; i--) {
        dst[i] = src[i]; // begin from the biggest
    }　
    return dst; */
}

// It is safe for the overlapping buffers unlike the memcpy in <string.h>.
// You should make sure that dst < src before you call this.
static inline void* memcpy_forward(void* dst, const void* src, size_t n) {
    /* size_t i;

    for (i = 0; i < n; i++) {
        dst[i] = src[i]; // begin from the smallest
    }
    return dst;*/
}


/*-- Implementation detials --*/

Vector* create_vector(Vector** vec_ptr) {
    Vector* p = malloc(sizeof(Vector)); // malloc and initial value 
    p->count = 0;
    p->capacity = 0;
    p->data = NULL; 

    if (NULL != vec_ptr) {
        *vec_ptr = p;
    }
    return p;
         
} 

void destroy_vector(Vector** vec_ptr) {
    if (NULL == vec_ptr) return;
    vec_clear(*vec_ptr);  
    (*vec_ptr)->capacity = 0;
    free((*vec_ptr)->data); // free is in destroy 
}

Vector* copy_vector(Vector* vec_src, Vector** vec_ptr) {
    Vector* vec = create_vector(NULL);
    vec_reserve(vec, vec_size(vec_src));
    memmove(vec_data(vec), vec_data(vec_src), vec_size(vec_src) * sizeof(value_type));
    vec->count = vec_size(vec_src);
    
    if (vec_ptr != NULL) {
        *vec_ptr = vec; // question !!!!! why not vec_ptr = &vec ? 
    }
    return vec;
}

size_t vec_size(Vector* vec) {
    return vec->count;
}

size_t vec_capacity(Vector* vec) {
    return vec->capacity / sizeof(C_VECTOR_VALUE_TYPE);
}

void vec_resize(Vector* vec, size_t n, value_type val) {
    vec_reserve(vec,n);

    if (n < vec_size(vec)) {
        vec->count = n;
    } else {
        size_t i;
        for (i = vec_size(vec); i < n; i++) 
            vec->data[i] = val; // set value to val  
        }
        vec->count = n;
}

int vec_empty(Vector* vec) {
    return vec_size(vec);
}

void vec_reserve(Vector* vec, size_t n) {
     if (n <= vec_capacity(vec)) {
        return ;
    } else {
        while (n > vec_capacity(vec)) {
            if(0 == vec_capacity(vec)) vec->capacity =  sizeof(value_type); // initial = 1
            vec->capacity = C_VECTOR_GROWTH_RATE *( vec_capacity(vec)) * sizeof(value_type); // rate = 2
            if (vec_capacity(vec) > C_VECTOR_MAX_SIZE) vec->capacity = C_VECTOR_MAX_SIZE; // max = MAX_SIZE
        }
        
        value_type* p = malloc(vec_capacity(vec) * sizeof(value_type));
        memmove(p, vec_data(vec), vec_size(vec) * sizeof(value_type));
        vec->data = p;
    }
}

value_type vec_get(Vector* vec, size_t n) {
    return vec->data[n];
}

void vec_set(Vector* vec, size_t n, value_type val) {
    vec->data[n] = val;
}

void vec_assign(Vector* vec, size_t size, value_type vals[]) {
    vec_reserve(vec,size);
    vec->count = size;
    memmove(vec_data(vec), vals, size * sizeof(value_type));
}

void vec_insert(Vector* vec, size_t n, size_t size, value_type vals[]) {

    vec_reserve(vec, size + vec_size(vec));

    memmove(vec_data(vec) + n + size, vec_data(vec) + n, (vec_size(vec) - n) * sizeof(value_type));
    memmove(vec_data(vec) + n, vals, size * sizeof(value_type)); // memmove  

    vec->count += size; // change count 
}

void vec_push_back(Vector* vec, value_type val) {
    vec_resize(vec, vec_size(vec) + 1, val);
}

value_type vec_front(Vector* vec) {
    return vec->data[0];
}

value_type vec_back(Vector* vec) {
    return vec->data[vec_size(vec)-1];
}

void vec_erase(Vector* vec, size_t n, size_t size) {
    memmove(vec_data(vec)+n,vec_data(vec)+n+size,(vec_size(vec)-n-size) * sizeof(value_type));
    vec->count-=size;  // memmove and change count 
}

void vec_pop_back(Vector* vec) {
    vec->count--;
}

void vec_clear(Vector* vec) {
    vec->count = 0;
}

value_type* vec_data(Vector* vec) {
    return vec->data;
}

