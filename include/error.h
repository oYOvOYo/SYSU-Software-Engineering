//
// error.h
// Copyright (C)  2016 jskyzero
//

typedef enum {
    EXPRESSION_ERROR,
    DIVIDE_BY_ZERO_ERROR,
    OVER_FLOW_ERROR
} ERROR;

void show_error_message(ERROR err);