//
// error.h
// Copyright (C)  2016 jskyzero
//
// define some errors and some func about error
//

#include "error.h"
#include <stdio.h>

// once this have error, can call this func to show error info
void show_error_message(ERROR err) {
  switch (err) {
    case EXPRESSION_ERROR:
      puts("EXPRESSION_ERROR");
      break;
    case DIVIDE_BY_ZERO_ERROR:
      puts("DIVIDE_BY_ZERO_ERROR");
      break;
    case OVER_FLOW_ERROR:
      puts("OVER_FLOW_ERROR");
      break;
    default:
      break;
  }
}

// check if there have the error
int check_have_error(int* error_code_ptr) { return *error_code_ptr > 0; }

// help to show call info whe debug
// attention have error
#include <string.h>
void show_info(const char* cal_str, int size, const char* str, int* p) {
  char a[size];
  strncpy(a, cal_str, size);

  if (*p == NO_ERROR) {
    printf("%s %s\n", str, a);
  }
  if (*p == NO_ERROR - 1) {
    printf("   %s %s\n", str, a);
  }
}