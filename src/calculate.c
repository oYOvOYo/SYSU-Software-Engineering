//
// calcute.c
// Copyright (C)  2016 jskyzero
//

#include "calculate.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef MAXINT
#define MAXINT  2147483647 // ((1<<31)-1)
#endif

static int eval(const char *cal_str, int offset, int *bounds);

static int node(const char *cal_str, int offset, int *bounds) {
  int pos = offset + 1;  // start from the second char

  if (cal_str[offset] == '(') {
    return eval(cal_str, pos, bounds);  // eval sub expression
  }
  if (cal_str[offset] == '-') {
    return -node(cal_str, pos, bounds);  // format: '-(x)'
  }

  for (pos; pos < *bounds; ++pos) {
    if (cal_str[pos] == '+' || cal_str[pos] == '-' || cal_str[pos] == '*' ||
        cal_str[pos] == '/' || cal_str[pos] == ')') {
      *bounds = pos;
      break;
    }
  }
  // printf("-%d-", atoi(cal_str + offset));
  return atoi(cal_str + offset);
}

static int eval(const char *cal_str, int offset, int *bounds) {
  int pos = *bounds;
  float left = node(cal_str, offset, &pos), right;  // get left node first

  // primary operations
  do {
    if (pos >= *bounds) {
      return left;  // finished
    }
    if (cal_str[pos] == ')') {
      *bounds = pos + 1;
      return left;  // end sub expression
    }

    offset = pos + 1;  // next node offset

    if (cal_str[pos] == '*') {
      pos = *bounds;
      left *= node(cal_str, offset, &pos);
      continue;
    }
    if (cal_str[pos] == '/') {
      pos = *bounds;
      right = node(cal_str, offset, &pos);
      if (right == 0)printf("Divide by zero error\n");
      left = (right == 0 ? MAXINT : left / right);
      continue;
    }

    break;
  } while (1);

  // secondary operations
  if (cal_str[pos] == '+') {
    return left + eval(cal_str, offset, bounds);
  }
  if (cal_str[pos] == '-') {
    return left + eval(cal_str, pos, bounds);  // x - y - z <=> x + (-y - z)
  }

  // error
  printf("Expression error\n");
  return MAXINT;
}

int calculate(const char *input_str) {
  size_t len = strlen(input_str);
  char *cal_str = (char *)malloc((len + 1) * sizeof(char));
  int i, j;
  int result;

  // remove white spaces
  memset(cal_str, sizeof(char) * len, 0);
  for (i = 0, j = 0; i < len; ++i) {
    if (input_str[i] != ' ' && input_str[i] != '\t') {
      cal_str[j] = input_str[i];
      ++j;
    }
  }

  // start
  result = eval(cal_str, 0, &j);
  free(cal_str);
  return result;
}