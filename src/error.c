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
