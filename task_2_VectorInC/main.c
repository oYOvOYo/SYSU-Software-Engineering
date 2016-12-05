// The main file for testing the C vector in task 2 simply.
// Copyright (c) 2016 sysu_AT. All righs reserved.

// This file could not ensure that your implementation of C vector is bug-free.
// You should complie this project in command-line as below:
//    "gcc -std=c99 -Wall -Werror -g main.c c_vector.c -o task_2"
// Pay Attention: You should not modify this file.

#include <stdio.h>
#include <assert.h>

#include "c_vector.h"

// Output all elements in vector in pretty format.
void vec_print(Vector* vec, const char* name) {
    printf("  %s: {", name);
	for (size_t i = 0; i < vec_size(vec); i++) {
        if (i != 0) printf(", "); 
		printf("%d", vec_get(vec, i));
	}
	printf("}\n");
}

int main() {
    Vector *vec_1 = NULL, *vec_2 = NULL;

    create_vector(&vec_1);
    printf("create vector 1 Done.\n");
    vec_2 = create_vector(NULL);
    printf("create_vector 2 Done.\n");

    printf("vec_1 size is %lu\n", vec_size(vec_1));
    printf("vec_2 size is %lu\n", vec_size(vec_2));

    printf("vec_1 capacity is %lu\n", vec_capacity(vec_1));
    printf("vec_2 capacity is %lu\n", vec_capacity(vec_2));

    // compound literal
    vec_assign(vec_1, 10, (value_type[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    // get pointer of data
    vec_assign(vec_2, 5, vec_data(vec_1));
    vec_assign(vec_2, 5, vec_data(vec_1) + 2);

    printf("vec_assign Done.\n");
    vec_print(vec_1, "vec_1"); // {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    vec_print(vec_2, "vec_2"); // {3, 4, 5, 6, 7}

    assert(*vec_data(vec_2) == vec_get(vec_2, 0));
    printf("vec_data Done.\n");

    vec_set(vec_1, 0, 99);
    assert(vec_get(vec_1, 0) == 99);
    assert(vec_get(vec_2, 0) == 3);
    printf("vec_set Done.\n");    
    printf("vec_get Done.\n");

    assert(vec_front(vec_1) == 99);
    printf("vec_front Done.\n");
    
    assert(vec_back(vec_2) == 7);
    printf("vec_back Done.\n");

    vec_push_back(vec_2, -1);
    vec_push_back(vec_2, 0);

    assert(vec_size(vec_2) == 7);
    printf("vec_push_back Done.\n");

    vec_pop_back(vec_1);
    assert(vec_size(vec_1) == 9);
    printf("vec_pop_back Done.\n");

    vec_print(vec_1, "vec_1"); // {99, 2, 3, 4, 5, 6, 7, 8, 9}
    vec_print(vec_2, "vec_2"); // {3, 4, 5, 6, 7, -1, 0}

    vec_erase(vec_1, 2, 5);
    assert(vec_size(vec_1) == 4);
    vec_erase(vec_2, 0, 4);
    assert(vec_size(vec_2) == 3);

    vec_insert(vec_1, 0, 2, (value_type[]){-99, -100});
    vec_insert(vec_2, 3, 1, (value_type[]){1});
    vec_insert(vec_2, 1, 2, (value_type[]){22, 40});

    vec_print(vec_1, "vec_1"); // {-99, -100, 99, 2, 8, 9}
    vec_print(vec_2, "vec_2"); // {7, 22, 40, -1, 0, 1}
    printf("vec_insert Done.\n");

    vec_clear(vec_1);
    vec_print(vec_1, "vec_1"); // {}
    printf("vec_clear Done.\n");

    destroy_vector(&vec_1);
    copy_vector(vec_2, &vec_1);
    vec_print(vec_1, "vec_1"); // {7, 22, 40, -1, 0, 1}
    printf("Destroy vector Done.\n");
    printf("Copy vector Done.\n");

    vec_resize(vec_1, 10, 0);
    vec_print(vec_1, "vec_1"); // {7, 22, 40, -1, 0, 1, 0, 0, 0, 0}

    for (size_t i = 0; i < vec_size(vec_1); i++)
        vec_set(vec_1, i, i);

    vec_print(vec_1, "vec_1"); // {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

    for (size_t i = 10; i < 100; i++)
        vec_push_back(vec_1, i);

    assert(vec_size(vec_1) == 100);

    value_type *p = vec_data(vec_1);
    for (size_t i = 0; i < vec_size(vec_1); i++)
        assert(p[i] == i);

    printf("vec_1 capacity is %lu\n", vec_capacity(vec_1));
    printf("vec_2 capacity is %lu\n", vec_capacity(vec_2));

    destroy_vector(&vec_1);
    destroy_vector(&vec_2);

    printf("\n[All Done].\n\n");

    return 0;
}
