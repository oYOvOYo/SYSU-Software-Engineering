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

const uint8_t MESSAGE_EXPANSION[] = {
    32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,  8,  9,  10, 11,
    12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

const uint8_t S_BOX[8][64] = {
    {14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0, 7,
     0,  15, 7,  4, 14, 2,  13, 1,  10, 6,  12, 11, 9,  5,  3, 8,
     4,  1,  14, 8, 13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5, 0,
     15, 12, 8,  2, 4,  9,  1,  7,  5,  11, 3,  14, 10, 0,  6, 13},
    {15, 1,  8,  14, 6,  11, 3,  4,  9,  7, 2,  13, 12, 0, 5,  10,
     3,  13, 4,  7,  15, 2,  8,  14, 12, 0, 1,  10, 6,  9, 11, 5,
     0,  14, 7,  11, 10, 4,  13, 1,  5,  8, 12, 6,  9,  3, 2,  15,
     13, 8,  10, 1,  3,  15, 4,  2,  11, 6, 7,  12, 0,  5, 14, 9},
    {10, 0,  9,  14, 6, 3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
     13, 7,  0,  9,  3, 4,  6,  10, 2,  8,  5,  14, 12, 11, 15, 1,
     13, 6,  4,  9,  8, 15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
     1,  10, 13, 0,  6, 9,  8,  7,  4,  15, 14, 3,  11, 5,  2,  12},
    {7,  13, 14, 3, 0,  6,  9,  10, 1,  2, 8, 5,  11, 12, 4,  15,
     13, 8,  11, 5, 6,  15, 0,  3,  4,  7, 2, 12, 1,  10, 14, 9,
     10, 6,  9,  0, 12, 11, 7,  13, 15, 1, 3, 14, 5,  2,  8,  4,
     3,  15, 0,  6, 10, 1,  13, 8,  9,  4, 5, 11, 12, 7,  2,  14},
    {2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0, 14, 9,
     14, 11, 2,  12, 4,  7,  13, 1,  5,  0,  15, 10, 3,  9, 8,  6,
     4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3, 0,  14,
     11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4, 5,  3},
    {12, 1,  10, 15, 9, 2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11,
     10, 15, 4,  2,  7, 12, 9,  5,  6,  1,  13, 14, 0,  11, 3,  8,
     9,  14, 15, 5,  2, 8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
     4,  3,  2,  12, 9, 5,  15, 10, 11, 14, 1,  7,  6,  0,  8,  13},
    {4,  11, 2,  14, 15, 0, 8,  13, 3,  12, 9, 7,  5,  10, 6, 1,
     13, 0,  11, 7,  4,  9, 1,  10, 14, 3,  5, 12, 2,  15, 8, 6,
     1,  4,  11, 13, 12, 3, 7,  14, 10, 15, 6, 8,  0,  5,  9, 2,
     6,  11, 13, 8,  1,  4, 10, 7,  9,  5,  0, 15, 14, 2,  3, 12},
    {13, 2,  8,  4, 6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7,
     1,  15, 13, 8, 10, 3,  7,  4,  12, 5,  6,  11, 0,  14, 9,  2,
     7,  11, 4,  1, 9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8,
     2,  1,  14, 7, 4,  10, 8,  13, 15, 12, 9,  0,  3,  5,  6,  11}};

const uint8_t P_PERMUTATION[] = {16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23,
                                 26, 5, 18, 31, 10, 2,  8,  24, 14, 32, 27,
                                 3,  9, 19, 13, 30, 6,  22, 11, 4,  25};

void process_unit(PROCESS_TYPE process_type, uint64_t* sub_keys,
                  uint8_t* block8_array) {
  uint64_t* block = (uint64_t*)malloc(sizeof(uint64_t));

  uint8_to_uint64(block8_array, block);

  map_uint64(block, INTIAL_PERMUTATION, 64);
  
  if (process_type == ENCRYPTION_MODE) {
    for (uint8_t i = 0; i < 16; i++) {
      iteration_unit(block, sub_keys[i]);
    }
  } else {
    for (uint8_t i = 16; i > 0; i--) {
      iteration_unit(block, sub_keys[i - 1]);
    }
  }

  // swap output R16L16
  uint64_t left = ((*block) & mask_uint64_from_to(32, 63)) >> 32;
  uint64_t right = (*block) & mask_uint64_from_to(0, 31);
  *block = left | (right << 32);

  map_uint64(block, INVERSE_PERMUTATION, 64);

  uint64_to_uint8(block, block8_array);
  free(block);
}

// iteration
void iteration_unit(uint64_t* block, uint64_t sub_key) {
  // Given two blocks L and R of bits, LR denotes the block
  // consisting of the bits of L followed by the bits of R.
  uint64_t left = ((*block) & mask_uint64_from_to(32, 63)) >> 32;
  uint64_t right = (*block) & mask_uint64_from_to(0, 31);

  uint64_t new_left = right;
  map_uint64(&right, MESSAGE_EXPANSION, 48);
  uint64_t new_right = left ^ feistel(right ^ sub_key);
  *block = new_right | (new_left << 32);
}

uint64_t feistel(uint64_t num) {
  uint64_t ans = 0;
  for (int i = 0; i < 8; i++) {
    uint64_t input = (num & mask_uint64_from_to(6 * i, 6 * i + 5)) >> (6 * i);
    uint64_t x = (input & mask_uint64_from_to(1, 4)) >> 1;
    uint64_t y = (input & mask_uint64(0)) & ((input & mask_uint64(5)) >> 4);
    uint64_t output = S_BOX[i][y * 16 + x] << (4 * i);
    ans = ans | output;
  }
  map_uint64(&ans, P_PERMUTATION, 32);
  return (ans & mask_uint64_from_to(0, 31));
}