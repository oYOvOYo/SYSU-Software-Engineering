//
// calcute.c
// Copyright (C)  2016 jskyzero
//

#include "calculate.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int int_add(int num1, int num2, int* have_error);
int int_sub(int num1, int num2, int* have_error);
int int_mul(int num1, int num2, int* have_error);
int int_div(int num1, int num2, int* have_error);

int expr(const char* cal_str, int size, int* have_error);
int term(const char* cal_str, int size, int* have_error);
int factor(const char* cal_str, int size, int* have_error);
int integer(const char* cal_str, int size, int* have_error);
int number(const char* cal_str, int size, int* have_error);
int digit(char ch, int* have_error);

int expr(const char* cal_str, int size, int* have_error) {
  if (*have_error) return 0;
  char* char_ptr;
  char_ptr = strchr(cal_str, '+');
  if (char_ptr)
    return int_add(
        term(cal_str, char_ptr - cal_str, have_error),
        expr(char_ptr + 1, size - (char_ptr - cal_str) - 1, have_error),
        have_error);
  char_ptr = strchr(cal_str, '-');
  if (char_ptr)
    return int_sub(
        term(cal_str, char_ptr - cal_str, have_error),
        expr(char_ptr + 1, size - (char_ptr - cal_str) - 1, have_error),
        have_error);
  return term(cal_str, size, have_error);
}

int term(const char* cal_str, int size, int* have_error) {
  if (*have_error) return 0;
  char* char_ptr;
  char_ptr = strchr(cal_str, '*');
  if (char_ptr)
    return int_mul(
        factor(cal_str, char_ptr - cal_str, have_error),
        term(char_ptr + 1, size - (char_ptr - cal_str) - 1, have_error),
        have_error);
  char_ptr = strchr(cal_str, '/');
  if (char_ptr)
    return int_div(
        factor(cal_str, char_ptr - cal_str, have_error),
        term(char_ptr + 1, size - (char_ptr - cal_str) - 1, have_error),
        have_error);
  return factor(cal_str, size, have_error);
}

int factor(const char* cal_str, int size, int* have_error) {
  if (*have_error) return 0;
  if ('(' == cal_str[0] && ')' == cal_str[size - 1])
    return expr(cal_str + 1, size - 2, have_error);
  return integer(cal_str, size, have_error);
}
int integer(const char* cal_str, int size, int* have_error) {
  if (*have_error) return 0;
  if ('+' == cal_str[0]) return number(cal_str + 1, size - 1, have_error);
  if ('-' == cal_str[0]) return -number(cal_str + 1, size - 1, have_error);
  return number(cal_str, size, have_error);
}

int number(const char* cal_str, int size, int* have_error) {
  if (*have_error) return 0;
  if (size <= 0) {
    show_error_message(EXPRESSION_ERROR);
    *have_error = 1;
    return 0;
  }

  return size == 1 ? digit(cal_str[0], have_error)
                   : int_add(int_mul(number(cal_str, size - 1, have_error), 10,
                                     have_error),
                             digit(cal_str[size - 1], have_error), have_error);
}

int digit(char ch, int* have_error) {
  if (*have_error) return 0;
  if (!isdigit(ch)) {
    show_error_message(EXPRESSION_ERROR);
    *have_error = 1;
    return 0;
  } else {
    return ch - '0';
  }
}

int int_add(int num1, int num2, int* have_error) {
  if (*have_error) return 0;
  int ans = num1 + num2;
  if ((ans ^ num1) >= 0 || (ans ^ num2) >= 0) {
    return ans;
  } else {
    show_error_message(OVER_FLOW_ERROR);
    *have_error = 1;
    return 0;
  }
}

int int_sub(int num1, int num2, int* have_error) {
  if (*have_error) return 0;
  return int_add(num1, -num2, have_error);
}

int int_mul(int num1, int num2, int* have_error) {
  if (*have_error) return 0;
  int ans = 0;
  while (num2--) {
    ans = int_add(ans, num1, have_error);
  }
  return ans;
}

int int_div(int num1, int num2, int* have_error) {
  if (*have_error) return 0;
  if (num2 == 0) {
    if (num1 != 0) {
      return 0;
    } else {
      show_error_message(DIVIDE_BY_ZERO_ERROR);
      *have_error = 1;
      return 0;
    }
  } else {
    return num1 / num2;
  }
}

int calculate(const char* input_str) {
  size_t len = strlen(input_str);
  char* cal_str = (char*)malloc((len + 1) * sizeof(char));
  int i, j;  // input_str index and cal_str index
  int result;

  // remove white spaces
  memset(cal_str, sizeof(char) * len, 0);
  for (i = 0, j = 0; i < len; ++i) {
    if (!isspace(input_str[i])) {
      cal_str[j] = input_str[i];
      ++j;
    }
  }

  // start
  int have_error = 0;
  result = expr(cal_str, j, &have_error);
  // result = eval(cal_str, 0, &j);
  free(cal_str);
  return have_error ? 0 : result;
}