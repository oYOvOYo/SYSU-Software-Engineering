/*
 *
 * def.c
 *
 * contail some global tool function
 *
 *
 * */

#include <def.h>

// check whether 
void check_file_open(FILE* file, char* file_path, char* mode) {
  if (!file) {
    printf("Could not open %s (use mode %s) ", file_path, mode);
    exit(1);
  }
}