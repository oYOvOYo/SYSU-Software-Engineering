/*
 * MD5 algorithm implemented in C.
 *
 * jskyzero 2017/10/16 SYSU
 * 
 */

#include <stdio.h>    // for puts, FILE, fopen, printf
#include <stdlib.h>   // for exit
#include <stdint.h>   // for uint8_t, uint32_t
#include <string.h>   // for memcpy, memset

// Constants are the integer part of the sines of integers (in radians) * 2^32.
const uint32_t T[64] = {
  0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
  0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
  0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
  0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
  0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
  0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
  0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
  0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
  0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
  0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
  0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
  0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
  0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
  0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
  0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };
   
// r specifies the per-round shift amounts
const uint8_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                      5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
   
// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// convert uint8 to uint32
void uint8_to_uint32(uint8_t* array, uint32_t* num) {
  memcpy(num, array, 4);
}
// convert uint32 to uint8
void uint32_to_uint8(uint32_t* num, uint8_t* array) {
  memcpy(array, num, 4);
}
// unit pricess
void process_unit(uint8_t* block, uint32_t* ans) {
  uint32_t a, b, c, d, X, g, swap_temp;
  // store old value
  a = ans[0];
  b = ans[1];
  c = ans[2];
  d = ans[3];
  // loop for 64 times
  for (uint8_t i = 0, j = 0; i < 64; i++) {
    if (i < 16) {
      g = (b & c) | ((~b) & d);
      j = i;
    } else if (i < 32) {
      g = (b & d) | (c & (~d));
      j = (1 + 5 * i ) % 16;
    } else if (i < 48) {
      g = b ^ c ^ d;
      j = (5 + 3 * i ) % 16;
    } else {
      g = c ^ (b | (~d));
      j = (7 * i ) % 16;
    }
    // read data
    uint8_to_uint32(block + (4 * j), &X);
    // I made a mistake here, so I write
    // you should always be calm
    swap_temp = d;
    d = c;
    c = b;
    b = b + LEFTROTATE((a + g + T[i] + X ), r[i]);
    a = swap_temp;
  }
  // store back
  ans[0] += a;
  ans[1] += b;
  ans[2] += c;
  ans[3] += d;
}
// print final answer when in little ending
void print_md5(int32_t* ans, char * message) {
  uint8_t * ans_p = (uint8_t *)ans;
  for (uint8_t i = 0; i < 16; i++)
    printf("%2.2x", ans_p[i]);
  printf("  %s\n", message);
}

int main(int argc, char*argv[]) {
  // check argurments number
  if (argc != 2) {
    puts("usage: md5 filename");
  }
  // open file to read
  FILE* in = fopen(argv[1], "rb");
  if (!in) {
    printf("check you hava read right for %s\n", argv[1]);
    exit(1);
  }
  // caluate info about file length
  fseek(in, 0L, SEEK_END);
  long file_size = ftell(in);
  uint64_t file_length_bit = (uint64_t)(file_size << 3);
  fseek(in, 0L, SEEK_SET);
  uint8_t last_block_size = file_size % 64;
  uint8_t padding_size = 64 - last_block_size;
  unsigned long total_block_num = file_size / 64 + 1;
  unsigned long now_read_block_num = 0;
  // initial block_unit
  uint8_t block_unit[64];
  memset(block_unit, 0, 64);
  uint32_t answer_buffer[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476,};
  // process file
  while (fread(block_unit, 1, 64, in)) {
    now_read_block_num++;
    // check is last block
    if (now_read_block_num == total_block_num) {
      // if (fread(block_unit, 1, last_block_size, in)) {
        memset(block_unit + last_block_size, 0x80, 1);
        if (padding_size > 8) {
          memcpy(block_unit + 56, &file_length_bit, 8);
          process_unit(block_unit, answer_buffer);
        } else {
          process_unit(block_unit, answer_buffer);
          memset(block_unit, 0, 64);
          memcpy(block_unit + 56, &file_length_bit, 8);
          process_unit(block_unit, answer_buffer);
        }
      // }
    } else {
      process_unit(block_unit, answer_buffer);
    }
    // always init to default
    memset(block_unit, 0, 64);
  }
  // print ans
  print_md5(answer_buffer, argv[1]);
  // close file
  fclose(in);
  return 0;
 }