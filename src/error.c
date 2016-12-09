//
// error.h
// Copyright (C)  2016 jskyzero
//
#include "error.h"
#include <stdio.h>



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
  }
}

int check_have_error(int * error_code_ptr) {
  return *error_code_ptr > 0; 
}

#include <string.h>
void show_info(const char* cal_str, int size, const char* str, int* p) {
  if (*p == 0) {
    char a[100] = {0};
    strncpy(a, cal_str, size);
    printf("%s %s\n", str, a);
  }
  if (*p == -1) {
    char a[100] = {0};
    strncpy(a, cal_str, size);
    printf("   %s %s\n", str, a);
  }
}