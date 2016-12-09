//
// error.h
// Copyright (C)  2016 jskyzero
//
// define some errors and some func about error
//

// error types

typedef enum {
  NO_ERROR,
  EXPRESSION_ERROR = 1,
  DIVIDE_BY_ZERO_ERROR,
  OVER_FLOW_ERROR
} ERROR;

// once this have error, can call this func to show error info
void show_error_message(ERROR err);

// check if there have the error
int check_have_error(int* error_code_ptr);

// help to show call info whe debug
// attention have error
void show_info(const char* cal_str, int size, const char* str, int* p);