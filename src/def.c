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

// convert uint8 to uint64
void uint8_to_uint64(uint8_t* array, uint64_t* num) {
  memcpy(num, array, 8);
}
// convert uint64 to uint8
void uint64_to_uint8(uint64_t* num, uint8_t* array) {
  memcpy(array, num, 8);
}