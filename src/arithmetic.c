#include "arithmetic.h"
#include <limits.h>

int int_add(int num1, int num2, int* have_error) {
  if (*have_error > 0) return 1;
  int ans = num1 + num2;
  if ((ans ^ num1) >= 0 || (ans ^ num2) >= 0) {
    return ans;
  } else {
    *have_error = OVER_FLOW_ERROR;
    return 1;
  }
}

int int_sub(int num1, int num2, int* have_error) {
  if (*have_error > 0) return 1;
  if (num2 == INT_MIN) {
    if (num1 == INT_MIN) {
      return 0;
    }
    if (num1 < INT_MAX) {
      num1 += 1;
      num2 += 1;
    }
    if (num1 == INT_MAX) {
      *have_error = OVER_FLOW_ERROR;
      return 1;
    }
  }
  return int_add(num1, -num2, have_error);
}

int int_mul(int num1, int num2, int* have_error) {
  if (*have_error > 0) return 1;
  int ans = 0;

  if (num1 == INT_MIN || num2 == INT_MIN) {
    if (num1 == 0 || num2 == 0) {
      return 0;
    }
    if (num1 == 1 || num2 == 1) {
      return INT_MIN;
    }
    *have_error = OVER_FLOW_ERROR;
    return 1;
  }

  int min = num1 < num2 ? num1 : num2;
  int max = num1 > num2 ? num1 : num2;
  if (min < 0) {
    min = -min;
    max = -max;
  }
  while (min--) {
    ans = int_add(ans, max, have_error);
  }
  return ans;
}

int int_div(int num1, int num2, int* have_error) {
  if (*have_error > 0) return 1;
  if (num2 == 0) {
    if (num1 != 0) {
      return 0;
    } else {
      *have_error = DIVIDE_BY_ZERO_ERROR;
      return 1;
    }
  } else {
    return num1 / num2;
  }
}