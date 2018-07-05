//
// calculate.h
// Copyright (C)  2016 jskyzero
//
// the main part of the calculate
//

#include "calculate.h"
#include <string.h>  // for strchr() strlen()
#include <stdlib.h>  // for malloc() free()
#include <ctype.h>   // for isdigit()
#include <limits.h>  // for INT_MIN

#ifndef ERROR_RETURN_VALUE
#define ERROR_RETURN_VALUE 1
#endif

#ifndef INT_MIN_STR
#define INT_MIN_STR "-2147483648"
#endif

typedef int (*analysis_func)(const char* cal_str, int size,
                             int* error_code_ptr);
typedef int (*int_calculate)(int left, int right, int* error_code_ptr);

// try to use right_func to analysis the right part str, if success change the
// flag
// cal_str size error_code_ptr : use to be analysised
// success                     : flag is success return Not zero
// left_func right_func        : analysis two part of the cal_str
// int_cal                     : basic operation to calculate left and right
int try_analysis(const char* cal_str, int size, int* error_code_ptr,
                 int* success, char cal_char, analysis_func left_func,
                 analysis_func right_func, int_calculate int_cal) {
  const char* char_ptr;  // cal_char positin
  int right, try_error;  // right part value

  char_ptr = strchr(cal_str, cal_char);
  // find the cal_char
  while (char_ptr) {
    try_error = NO_ERROR - 1;  // A value to be different with ERROR
    // cal_char positin must from (0, size], can't be in first!!
    if (0 < (char_ptr - cal_str) && (char_ptr - cal_str) <= size) {
      right =  // try to analysis right
          right_func(char_ptr + 1, size - (char_ptr - cal_str) - 1, &try_error);
      if (try_error <= 0) {  // if sucess
        *success = 1;        // change flag
        // return int_cal(left, right)
        return int_cal(left_func(cal_str, char_ptr - cal_str, error_code_ptr),
                       right, error_code_ptr);
      }
    }
    // update positin for this loop
    char_ptr = strchr(char_ptr + 1, cal_char);
  }
  // if can't analysis anyway
  return ERROR_RETURN_VALUE;
}

int additive_expression(const char* cal_str, int size, int* error_code_ptr) {
  // show_info(cal_str, size, "additive_expression", error_code_ptr);
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  int return_value, can_analysis = 0;

  // <AdditiveExpression> "+" <MultipleExpression>
  return_value =
      try_analysis(cal_str, size, error_code_ptr, &can_analysis, '+',
                   additive_expression, multiple_expression, int_add);
  if (can_analysis) return return_value;

  // <AdditiveExpression> "-" <MultipleExpression>
  return_value =
      try_analysis(cal_str, size, error_code_ptr, &can_analysis, '-',
                   additive_expression, multiple_expression, int_sub);
  if (can_analysis) return return_value;

  // <MultipleExpression>
  return multiple_expression(cal_str, size, error_code_ptr);
}

int multiple_expression(const char* cal_str, int size, int* error_code_ptr) {
  // show_info(cal_str, size, "multiple_expression", error_code_ptr);
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  int return_value, can_analysis = 0;

  // <MultipleExpression> "*" <PrimaryExpression>
  return_value = try_analysis(cal_str, size, error_code_ptr, &can_analysis, '*',
                              multiple_expression, primary_expression, int_mul);
  if (can_analysis) return return_value;

  // <MultipleExpression> "/" <PrimaryExpression>
  return_value = try_analysis(cal_str, size, error_code_ptr, &can_analysis, '/',
                              multiple_expression, primary_expression, int_div);
  if (can_analysis) return return_value;

  // <PrimaryExpression>
  return primary_expression(cal_str, size, error_code_ptr);
}

int primary_expression(const char* cal_str, int size, int* error_code_ptr) {
  // show_info(cal_str, size, "primary_expression", error_code_ptr);
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  // "(" <Expression> ")"
  // <Expression> ::=  <AdditiveExpression>
  if ('(' == cal_str[0] && ')' == cal_str[size - 1]) {
    return additive_expression(cal_str + 1, size - 2, error_code_ptr);
  }
  //  <Integer>
  return integer(cal_str, size, error_code_ptr);
}

int integer(const char* cal_str, int size, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  //  "-" <Number>
  if (0 == strncmp(cal_str, INT_MIN_STR, strlen(INT_MIN_STR))) return INT_MIN;
  if ('+' == cal_str[0]) return number(cal_str + 1, size - 1, error_code_ptr);

  // "+" <number>
  if ('-' == cal_str[0]) return -number(cal_str + 1, size - 1, error_code_ptr);

  //  <number>
  return number(cal_str, size, error_code_ptr);
}

int number(const char* cal_str, int size, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  if (size <= 0) {
    *error_code_ptr = EXPRESSION_ERROR;
    return ERROR_RETURN_VALUE;
  }

  // <digit>
  if (size == 1) {
    return digit(cal_str[0], error_code_ptr);
    //<digit> <number>
  } else {
    return int_add(
        int_mul(number(cal_str, size - 1, error_code_ptr), 10, error_code_ptr),
        digit(cal_str[size - 1], error_code_ptr), error_code_ptr);
  }
}

int digit(char ch, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  if (!isdigit(ch)) {
    *error_code_ptr = EXPRESSION_ERROR;
    return ERROR_RETURN_VALUE;
  } else {
    //  "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
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
  result = additive_expression(cal_str, j, &error_code);
  free(cal_str);
  if (error_code) {
    show_error_message(error_code);
    return 0;
  } else
    return result;
}