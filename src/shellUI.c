//
// shellUI.c
// Copyright (C)  2016 jskyzero
//

#include <stdio.h>
#include <stdlib.h>
#include "shellUI.h"

#ifndef STRING_LENGTH
#define STRING_LENGTH (1 << 16)
#endif


void ShellUI(void) {
  char *input_str = (char *)malloc(STRING_LENGTH * sizeof(char));

  while (printf(">> "), fgets(input_str, STRING_LENGTH, stdin) != NULL) {
    printf("%d\n", calculate(input_str));
  }

  free(input_str);
}