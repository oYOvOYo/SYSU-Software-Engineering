//
// arithmetic.h
// Copyright (C)  2016 jskyzero
//
// basic arithmetic using only int
//

#include "arithmetic.h"

#include <limits.h>  // for INT_MAX INT_MIN

#ifndef ERROR_RETURN_VALUE
#define ERROR_RETURN_VALUE 1
#endif

int int_add(int left, int right, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  int ans = left + right;
  // thre is no overflow
  if ((ans ^ left) >= 0 || (ans ^ right) >= 0) {
    return ans;
  } else {
    *error_code_ptr = OVER_FLOW_ERROR;
    return ERROR_RETURN_VALUE;
  }
}

int int_sub(int left, int right, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  if (right == INT_MIN) {
    // check the sitution if the right value is INT_MIN
    if (left == INT_MIN) {
      return 0;
    }
    // incase -INT_MIN or left + 1 will overflow
    if (left < INT_MAX) {
      left += 1;
      right += 1;
    }
    // of course, overflow
    if (left == INT_MAX) {
      *error_code_ptr = OVER_FLOW_ERROR;
      return ERROR_RETURN_VALUE;
    }
  }
  return int_add(left, -right, error_code_ptr);
}

int int_mul(int left, int right, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  int ans = 0;
  // check the sutuation there is a INT_MIN in left or right
  if (left == INT_MIN || right == INT_MIN) {
    // 0 * anyvalue = 0
    if (left == 0 || right == 0) {
      return 0;
    }
    // 1 * anyvalue = anyvalue
    if (left == 1 || right == 1) {
      return INT_MIN;
    }
    // overflow
    *error_code_ptr = OVER_FLOW_ERROR;
    return ERROR_RETURN_VALUE;
  }
  // in other commen case
  int min = left < right ? left : right;
  int max = left > right ? left : right;
  
  // in case while loop
  if (min < 0) {
    min = -min;
    max = -max;
  }
  while (min--) {
    ans = int_add(ans, max, error_code_ptr);
  }
  return ans;
}

int int_div(int left, int right, int* error_code_ptr) {
  if (check_have_error(error_code_ptr)) return ERROR_RETURN_VALUE;

  if (right == 0) {
    if (left != 0) {
      // 0 / 0 will not cause a error
      return 0;
    } else {
      // Not 0 / 0 will cause a error
      *error_code_ptr = DIVIDE_BY_ZERO_ERROR;
      return ERROR_RETURN_VALUE;
    }
  } else {
    // integer devide
    return left / right;
  }
}