//
// error.h
// Copyright (C)  2016 jskyzero
//
// define some errors and show the error 
//

typedef enum {
    NO_ERROR,
    EXPRESSION_ERROR=1,
    DIVIDE_BY_ZERO_ERROR,
    OVER_FLOW_ERROR
} ERROR;

void show_error_message(ERROR err);
int check_have_error(int * error_code_ptr);

void show_info(const char* cal_str, int size, const char* str, int* p);