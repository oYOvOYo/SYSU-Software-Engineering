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
void map_uint64(uint64_t* num, const uint8_t* table, uint8_t length) {
  uint64_t initial = *num;
  uint64_t answer = initial;
  uint64_t need_bit;
  for (uint8_t i = 0; i < length; i++) {
    // first we set i bit to zero
    answer = answer & (~mask_uint64(i));
    // then we store need bit
    uint64_t temp = mask_uint64(table[i] - 1);
    need_bit = ((initial & mask_uint64(table[i] - 1)) >> (table[i] -1 ));
    // last we set i bit to need bit
    answer = answer | (need_bit << i);
  }
  *num = answer; 
}

// procude each bit mask from 0 bit to 63 bit
uint64_t mask_uint64(uint8_t index) {
  uint64_t num = 1;
  return num << index;
}

// procude mask from 0 bit to 63 bit
uint64_t mask_uint64_from_to(uint8_t begin, uint8_t end) {
  uint64_t left_mask = UINT64_MAX << begin ;
  uint64_t right_mask = UINT64_MAX >> (64 - end - 1);
  // save the join part
  uint64_t num = left_mask & right_mask;
  return num;
}