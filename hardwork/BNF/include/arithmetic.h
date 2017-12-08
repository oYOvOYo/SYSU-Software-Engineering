//
// arithmetic.h
// Copyright (C)  2016 jskyzero
//
// basic arithmetic using only int
//

#include "error.h"

int int_add(int left, int right, int* error_code_ptr);
int int_sub(int left, int right, int* error_code_ptr);
int int_mul(int left, int right, int* error_code_ptr);
int int_div(int left, int right, int* error_code_ptr);