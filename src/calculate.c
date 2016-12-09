//
// calcute.c
// Copyright (C)  2016 jskyzero
//

#include "calculate.h"
#include <string.h>  // for strchr() strlen()
#include <stdlib.h>  // for malloc() free()
#include <ctype.h>   // for isdigit()
#include <limits.h>  // for INT_MIN

typedef int (*analysis_func)(const char* cal_str, int size, int* have_error);
typedef int (*int_calculate)(int num1, int num2, int* have_error);

int try_analysis(const char* cal_str, int size, int* have_error, int* success,
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
        return int_cal(left_func(cal_str, char_ptr - cal_str, have_error),
                       right, have_error);
      }
    }
    char_ptr = strchr(char_ptr + 1, cal_char);
  }
  return 1;
}

int expr(const char* cal_str, int size, int* have_error) {
  // show_info(cal_str, size, "expr", have_error);
  if (*have_error > 0) return 1;
  
  int return_value, can_analysis = 0;
  
  return_value = try_analysis(cal_str, size, have_error, &can_analysis, '+',
                                  expr, term, int_add);
  if (can_analysis) return return_value;

  return_value = try_analysis(cal_str, size, have_error, &can_analysis, '-',
                                  expr, term, int_sub);
  if (can_analysis) return return_value;

  return term(cal_str, size, have_error);
}

int term(const char* cal_str, int size, int* have_error) {
  // show_info(cal_str, size, "term", have_error);
  if (*have_error > 0) return 1;
  int return_value, can_analysis = 0;
  
  return_value = try_analysis(cal_str, size, have_error, &can_analysis, '*',
                                  term, factor, int_mul);
  if (can_analysis) return return_value;

  return_value = try_analysis(cal_str, size, have_error, &can_analysis, '/',
                                  term, factor, int_div);
  if (can_analysis) return return_value;

  return factor(cal_str, size, have_error);
}

int factor(const char* cal_str, int size, int* have_error) {
  // show_info(cal_str, size, "factor", have_error);
  if (*have_error > 0) return 1;
  if ('(' == cal_str[0] && ')' == cal_str[size - 1]) {
    return expr(cal_str + 1, size - 2, have_error);
  }
  return integer(cal_str, size, have_error);
}

int integer(const char* cal_str, int size, int* have_error) {
  if (*have_error > 0) return 1;

  if (0 == strncmp(cal_str, "-2147483648", 11)) return INT_MIN;
  if ('+' == cal_str[0]) return number(cal_str + 1, size - 1, have_error);
  if ('-' == cal_str[0]) return -number(cal_str + 1, size - 1, have_error);
  return number(cal_str, size, have_error);
}

int number(const char* cal_str, int size, int* have_error) {
  if (*have_error > 0) return 1;
  if (size <= 0) {
    *have_error = EXPRESSION_ERROR;
    return 1;
  }

  return size == 1 ? digit(cal_str[0], have_error)
                   : int_add(int_mul(number(cal_str, size - 1, have_error), 10,
                                     have_error),
                             digit(cal_str[size - 1], have_error), have_error);
}

int digit(char ch, int* have_error) {
  if (*have_error > 0) return 1;
  if (!isdigit(ch)) {
    *have_error = EXPRESSION_ERROR;
    return 1;
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
  int have_error = 0;
  result = expr(cal_str, j, &have_error);
  free(cal_str);
  if (have_error) {
    show_error_message(have_error);
    return 0;
  } else
    return result;
}