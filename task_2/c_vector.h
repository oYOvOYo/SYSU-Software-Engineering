// The header of a dynamic array -- C vector in task 2.
// Copyright (c) 2016 sysu_AT. All righs reserved.

/*
 * Vectors are sequence containers representing arrays that can
 *    change in size. Their size can change dynamically, with their
 *    storage being handled automatically by the container.
 * For details: http://www.cplusplus.com/reference/vector/vector/
 */

// You should not modify this file.

#ifndef TASK_C_VECTOR_H_
#define TASK_C_VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* Definition of some constant values */

#define C_VECTOR_VALUE_TYPE     int
#define C_VECTOR_MAX_SIZE       ((size_t)(-1) / sizeof(C_VECTOR_VALUE_TYPE) - 1)
#define C_VECTOR_GROWTH_RATE    2


/*-- Definition of the struction of C vector --*/

    typedef C_VECTOR_VALUE_TYPE value_type;

    typedef struct {
        size_t count; // used size
        size_t capacity; // data[] size
        value_type* data; // the pointer of array which stores the elements
    } Vector;


/*-- initialization and destruction of C vector --*/

    // Create a vector and initialize it.  It will allocate the memory and
    //    return the pointer of Vector, and if the argument is not a null
    //    pointer, it also sets this value to the object pointed.
    Vector* create_vector(Vector** vec);

    // Destroy a vector which had been created.  It will deallocate the memory
    //    and if vec is a null pointer, the function does nothing.
    void destroy_vector(Vector** vec);

    // Create a vector on *vec and copy all the elements from vec_src to it.
    // It will allocate the memory and return the pointer of Vector, and if
    //    the second argument is not a null pointer, it also sets this value
    //    to the object pointed.
    Vector* copy_vector(Vector* vec_src, Vector** vec);


/*-- member functions of C vector --*/

    // Return the size of element in the vector.
    size_t vec_size(Vector* vec);

    // Return the capacity of the storage space currently allocated for the
    //    vector, expressed in terms of elements.
    size_t vec_capacity(Vector* vec);

    // Resize the container so that it contains n elements.
    // If n is smaller than the current container size, the content is reduced
    //    to its first n elements, removing those beyond (but will not ensure
    //    to destroy them).
    // If n is greater than the current container size, the content is expanded
    //    by inserting at the end as many elements as needed to reach a size of
    //    n. The new elements are initialized as copies of val.
    // If n is also greater than the current container capacity, an automatic
    //    reallocation of the allocated storage space takes place.
    void vec_resize(Vector* vec, size_t n, value_type val);

    // Return a value different from zero if it is empty.
    int vec_empty(Vector* vec);

    // Requests that the vector capacity be at least enough to contain n
    //    elements.
    void vec_reserve(Vector* vec, size_t n);

    // Return the value of element in position n in the vector.
    value_type vec_get(Vector* vec, size_t n);

    // Set the value of element in position n in the vector.
    void vec_set(Vector* vec, size_t n, value_type val);

    // Assigns new contents to the vector, replacing its current contents, and
    //    modifying its size accordingly.
    void vec_assign(Vector* vec, size_t size, value_type vals[]);

    // Extend the vector by inserting new elements before the element at
    //    the specified position in vector.
    void vec_insert(Vector* vec, size_t n, size_t size, value_type vals[]);

    // Add a new element at the end of the vector, after its current last
    //    element. 
    void vec_push_back(Vector* vec, value_type val);

    // Return the value of the first element in the vector.
    value_type vec_front(Vector* vec);

    // Return the value of the the last element in the vector.
    value_type vec_back(Vector* vec);

    // Removes from the vector a range of elements in [n, n + size).
    void vec_erase(Vector* vec, size_t n, size_t size);

    // Remove the last element in the vector, effectively reducing the
    //    container size by one.
    void vec_pop_back(Vector* vec);

    // Remove all elements from the vector (which are destroyed), leaving
    //    the container with a size of 0.
    void vec_clear(Vector* vec);

    // Return a direct pointer to the memory array used internally by the vector
    //    to store its owned elements.
    value_type* vec_data(Vector* vec);


#ifdef __cplusplus
}
#endif

#endif // TASK_C_VECTOR_H_