//
// shellUI.c
// Copyright (C)  2016 jskyzero
//

#include "shellUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef STRING_LENGTH
#define STRING_LENGTH (INT_MAX / 2)
#endif


void ShellUI(void) {
  
  // delete it if you do not to test  
  // test(); 


  char *input_str = (char *)malloc(STRING_LENGTH * sizeof(char));

  while (printf(">> "), fgets(input_str, STRING_LENGTH, stdin) != NULL) {
    printf("%d\n", calculate(input_str));
  }

  free(input_str);
}
