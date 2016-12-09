//
// calcute.c
// Copyright (C)  2016 jskyzero
//

#include "calculate.h"
#include <string.h>  // for strchr() strlen()
#include <stdlib.h>  // for malloc() free()
#include <ctype.h>   // for isdigit()
#include <limits.h>  // for INT_MIN

#ifndef ERROR_RETURN_VALUE
#define ERROR_RETURN_VALUE 1
#endif


typedef int (*analysis_func)(const char* cal_str, int size, int* error_code_ptr);
typedef int (*int_calculate)(int num1, int num2, int* error_code_ptr);

int try_analysis(const char* cal_str, int size, int* error_code_ptr, int* success,
                 char cal_char, analysis_func left_func,
                 analysis_func right_func, int_calculate int_cal) {
  const char* char_ptr;
  int right, try_error;

  char_ptr = strchr(cal_str, cal_char);
  while (char_ptr) {
    try_error = -1;
    if (0 < (char_ptr - cal_str) && (char_ptr - cal_str) <= size) {
      right =
          right_func(char_ptr + 1, size - (char_ptr - cal_str) - 1, &try_error);
      if (try_error <= 0) {
        *success = 1;
        return int_cal(left_func(cal_str, char_ptr - cal_str, error_code_ptr),
                       right, error_code_ptr);
      }
    }
    char_ptr = strchr(char_ptr + 1, cal_char);
  }
  return ERROR_RETURN_VALUE;
}

int expr(const char* cal_str, int size, int* error_code_ptr) {
  // show_info(cal_str, size, "expr", error_code_ptr);
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;
  
  int return_value, can_analysis = 0;
  
  return_value = try_analysis(cal_str, size, error_code_ptr, &can_analysis, '+',
                                  expr, term, int_add);
  if (can_analysis) return return_value;

  return_value = try_analysis(cal_str, size, error_code_ptr, &can_analysis, '-',
                                  expr, term, int_sub);
  if (can_analysis) return return_value;

  return term(cal_str, size, error_code_ptr);
}

int term(const char* cal_str, int size, int* error_code_ptr) {
  // show_info(cal_str, size, "term", error_code_ptr);
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;
  int return_value, can_analysis = 0;
  
  return_value = try_analysis(cal_str, size, error_code_ptr, &can_analysis, '*',
                                  term, factor, int_mul);
  if (can_analysis) return return_value;

  return_value = try_analysis(cal_str, size, error_code_ptr, &can_analysis, '/',
                                  term, factor, int_div);
  if (can_analysis) return return_value;

  return factor(cal_str, size, error_code_ptr);
}

int factor(const char* cal_str, int size, int* error_code_ptr) {
  // show_info(cal_str, size, "factor", error_code_ptr);
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;
  if ('(' == cal_str[0] && ')' == cal_str[size - 1]) {
    return expr(cal_str + 1, size - 2, error_code_ptr);
  }
  return integer(cal_str, size, error_code_ptr);
}

int integer(const char* cal_str, int size, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  if (0 == strncmp(cal_str, "-2147483648", 11)) return INT_MIN;
  if ('+' == cal_str[0]) return number(cal_str + 1, size - 1, error_code_ptr);
  if ('-' == cal_str[0]) return -number(cal_str + 1, size - 1, error_code_ptr);
  return number(cal_str, size, error_code_ptr);
}

int number(const char* cal_str, int size, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;
  if (size <= 0) {
    *error_code_ptr = EXPRESSION_ERROR;
    return ERROR_RETURN_VALUE;
  }

  return size == 1 ? digit(cal_str[0], error_code_ptr)
                   : int_add(int_mul(number(cal_str, size - 1, error_code_ptr), 10,
                                     error_code_ptr),
                             digit(cal_str[size - 1], error_code_ptr), error_code_ptr);
}

int digit(char ch, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;
  if (!isdigit(ch)) {
    *error_code_ptr = EXPRESSION_ERROR;
    return ERROR_RETURN_VALUE;
  } else {
    return ch - '0';
  }
}

int calculate(const char* input_str) {
  size_t len = strlen(input_str);
  char* cal_str = (char*)malloc((len + 1) * sizeof(char));
  int i, j;  // input_str index and cal_str index
  int result;

  // remove white spaces
  for (i = 0, j = 0; i < len; ++i) {
    if (!isspace(input_str[i])) {
      cal_str[j] = input_str[i];
      ++j;
    }
  }
  cal_str[j] = '\0';
  // start
  int error_code = 0;
  result = expr(cal_str, j, &error_code);
  free(cal_str);
  if (error_code) {
    show_error_message(error_code);
    return 0;
  } else
    return result;
}