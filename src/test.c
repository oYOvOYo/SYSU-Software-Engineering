#include "test.h"
#include <assert.h>  // for assert
#include <limits.h>  // fot INT_MAX INT_MIN
#include <stdio.h>   // for puts
#include <string.h>  // for memset, strcpy, strcpy
#include <stdlib.h>  // for malloc
void test(void) {
  int have_error = 0;
  assert(2 == int_add(1, 1, &have_error) && have_error == 0);
  assert(100 == int_add(50, 50, &have_error) && have_error == 0);
  assert(INT_MAX == int_add(INT_MAX, 0, &have_error) && have_error == 0);
  assert(INT_MIN == int_add(INT_MIN, 0, &have_error) && have_error == 0);
  assert(0 == int_add(INT_MAX, -INT_MAX, &have_error) && have_error == 0);
  assert(-1 == int_add(INT_MAX, INT_MIN, &have_error) && have_error == 0);
  assert(-1 == int_add(INT_MIN, INT_MAX, &have_error) && have_error == 0);
  assert(1 == int_add(INT_MAX, 1, &have_error) &&
         have_error == OVER_FLOW_ERROR);
  have_error = 0;
  assert(1 == int_add(INT_MIN, -1, &have_error) &&
         have_error == OVER_FLOW_ERROR);
  puts("int_add finished");

  have_error = 0;
  assert(2 == int_sub(1, -1, &have_error) && have_error == 0);
  assert(0 == int_sub(-1, -1, &have_error) && have_error == 0);
  assert(0 == int_sub(INT_MAX, INT_MAX, &have_error) && have_error == 0);
  assert(0 == int_sub(INT_MIN, INT_MIN, &have_error) && have_error == 0);
  assert(-INT_MAX == int_sub(0, INT_MAX, &have_error) && have_error == 0);
  assert(-1 == int_sub(INT_MIN, -INT_MAX, &have_error) && have_error == 0);
  assert(INT_MAX == int_sub(-1, INT_MIN, &have_error) && have_error == 0);
  assert(1 == int_sub(INT_MAX, INT_MIN, &have_error) &&
         have_error == OVER_FLOW_ERROR);
  have_error = 0;
  assert(1 == int_sub(0, INT_MIN, &have_error) &&
         have_error == OVER_FLOW_ERROR);
  puts("int_sub finished");

  have_error = 0;
  assert(INT_MAX == int_mul(INT_MAX, 1, &have_error) && have_error == 0);
  assert(-INT_MAX == int_mul(INT_MAX, -1, &have_error) && have_error == 0);
  assert(0 == int_mul(INT_MAX, 0, &have_error) && have_error == 0);
  assert(INT_MIN == int_mul(INT_MIN, 1, &have_error) && have_error == 0);
  assert(0 == int_mul(INT_MIN, 0, &have_error) && have_error == 0);
  assert(1 == int_mul(INT_MIN, -1, &have_error) &&
         have_error == OVER_FLOW_ERROR);
  puts("int_mul finished");

  have_error = 0;
  assert(0 == int_div(0, INT_MIN, &have_error) && have_error == 0);
  assert(0 == int_div(0, INT_MAX, &have_error) && have_error == 0);
  assert(-1 == int_div(-1, 1, &have_error) && have_error == 0);
  assert(-1 == int_div(1, -1, &have_error) && have_error == 0);
  puts("int_div finished");

  // random test
  assert(1 == calculate("1"));
  assert(-18 == calculate(" (1+2)-1*19-(2-2)-2+1 * 2 / 3 - 12+12"));

  assert(42167754 ==
         calculate("1+2324-134/1244*134-(23412-(12340*3419-385-1234))"));
  assert(50918778 == calculate("1+2324-134/"
                               "1244*134-(23412-(12340*3419-385-1234))+345-452*"
                               "345/3452+(24-42*(34-452-45)*450)"));
  const int brackets_length = 1 << 15;
  const char in_str[] = "1";
  const char end_str[] = "+1";
  char *input_str = (char *)malloc(
      (1 + 2 * brackets_length + strlen(in_str) + strlen(end_str)) * sizeof(char));
  memset(input_str, '(', brackets_length);
  strcpy(input_str + brackets_length, in_str);
  memset(input_str + brackets_length + strlen(in_str), ')', brackets_length);
  strcpy(input_str + (2 * brackets_length + strlen(in_str)), end_str);
  // puts(input_str);
  //   assert(0 == strcmp(input_str, "(1)+1"));
  assert(2 == calculate(input_str));
  free(input_str);
  puts("tests finished");
}
