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

// map bit of uint64
void map_uint64(uint64_t* num, uint8_t* table) {
  uint64_t initial = *num;
  uint64_t answer = initial;
  uint64_t need_bit;
  for (uint8_t i = 0; i < sizeof(table) - 1; i++) {
    // first we set i bit to zero
    answer = answer & (~mask_uint64(i + 1));
    // then we store need bit
    need_bit = ((initial & mask_uint64(table[i])) >> (table[i] -1 ));
    // last we set i bit to 
    answer = answer | (need_bit << ((i + 1) - 1));
  }
  *num = answer; 
}

// procude mask from 1 bit to 64 bit
uint64_t mask_uint64(uint8_t index) {
  return (uint64_t)(1 << (index - 1));
}