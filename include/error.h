//
// error.h
// Copyright (C)  2016 jskyzero
//
// define some errors and show the error 
//

typedef enum {
    EXPRESSION_ERROR=1,
    DIVIDE_BY_ZERO_ERROR,
    OVER_FLOW_ERROR
} ERROR;

void show_error_message(ERROR err);
void show_info(const char* cal_str, int size, const char* str, int* p);