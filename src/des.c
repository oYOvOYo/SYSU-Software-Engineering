/*
 *
 * des.c
 *
 * main unit process part of des
 *
 * */

#include <des.h>

const uint8_t INTIAL_PERMUTATION[] = {
  58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
  62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
  57, 49, 41, 33, 25, 17, 9,  1, 59, 51, 43, 35, 27, 19, 11, 3,
  61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

const uint8_t INVERSE_PERMUTATION[] = {
  40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
  38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
  36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
  34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9,  49, 17, 57, 25};


void process_unit(PROCESS_TYPE process_type, uint64_t* sub_keys,
                  uint8_t* block8_array) {
  uint64_t* block = (uint64_t *)malloc(sizeof(uint64_t));
  uint8_to_uint64(block8_array, block);

  map_uint64(block, INTIAL_PERMUTATION, 64);
  map_uint64(block, INVERSE_PERMUTATION, 64);
  
  uint64_to_uint8(block, block8_array);
  free(block);
}