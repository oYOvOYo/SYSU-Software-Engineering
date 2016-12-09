#include "test.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

void test(void) {
    int have_error = 0;
    assert(2 == int_add(1, 1, &have_error) && have_error == 0);
    assert(100 == int_add(50, 50, &have_error) && have_error == 0);
    assert(INT_MAX == int_add(INT_MAX, 0, &have_error) && have_error == 0);
    assert(INT_MIN == int_add(INT_MIN, 0, &have_error) && have_error == 0);
    assert(0 == int_add(INT_MAX, -INT_MAX, &have_error) && have_error == 0);
    assert(-1 == int_add(INT_MAX, INT_MIN, &have_error) && have_error == 0);
    assert(-1 == int_add(INT_MIN, INT_MAX, &have_error) && have_error == 0);
    assert(1 == int_add(INT_MAX, 1, &have_error) && have_error == OVER_FLOW_ERROR);
    have_error = 0;
    assert(1 == int_add(INT_MIN, -1, &have_error) && have_error == OVER_FLOW_ERROR);
    puts("int_add finished");

    have_error = 0;
    assert(2 == int_sub(1, -1, &have_error) && have_error == 0);
    assert(0 == int_sub(-1, -1, &have_error) && have_error == 0);
    assert(0 == int_sub(INT_MAX, INT_MAX, &have_error) && have_error == 0);
    assert(0 == int_sub(INT_MIN, INT_MIN, &have_error) && have_error == 0);
    assert(-INT_MAX == int_sub(0, INT_MAX, &have_error) && have_error == 0);
    assert(-1 == int_sub(INT_MIN, -INT_MAX, &have_error) && have_error == 0);
    assert(INT_MAX == int_sub(-1, INT_MIN, &have_error) && have_error == 0);
    assert(1 == int_sub(INT_MAX, INT_MIN, &have_error) && have_error == OVER_FLOW_ERROR);
    have_error = 0;
    assert(1 == int_sub(0, INT_MIN, &have_error) && have_error == OVER_FLOW_ERROR);
    puts("int_sub finished");


    have_error = 0;
    assert(INT_MAX == int_mul(INT_MAX, 1, &have_error) && have_error == 0);
    assert(-INT_MAX == int_mul(INT_MAX, -1, &have_error) && have_error == 0);
    assert(0 == int_mul(INT_MAX, 0, &have_error) && have_error == 0);
    assert(INT_MIN == int_mul(INT_MIN, 1, &have_error) && have_error == 0);
    assert(0 == int_mul(INT_MIN, 0, &have_error) && have_error == 0);
    assert(1 == int_mul(INT_MIN, -1, &have_error) && have_error == OVER_FLOW_ERROR);
    puts("int_mul finished");
}