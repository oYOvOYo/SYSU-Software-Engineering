/*
 * MD5 algorithm implemented in C.
 * jskyzero 2017/10/16 SYSU
 * 
 */

#include <stdio.h>    // for puts, FILE, fopen, printf
#include <stdlib.h>   // for exit
#include <stdint.h>   // for uint8_t, uint32_t
#include <string.h>   // for memcpy, memset

// convert uint8 to uint64
void uint8_to_uint64(uint8_t* array, uint64_t* num) {
  memcpy(num, array, 8);
}
// convert uint64 to uint8
void uint64_to_uint8(uint64_t* num, uint8_t* array) {
  memcpy(array, num, 8);
}

void process_init(uint32_t* block, uint32_t* ans) {

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
  // initial block_uint
  uint8_t block_unit[64];
  memset(block_unit, 0, 64);
  // process file
  while (fread(block_unit, 1, 64, in)) {
    now_read_block_num++;

    if (now_read_block_num == total_block_num) {
      if (fread(block_unit, 1, last_block_size, in)) {
        memset(block_unit + last_block_size, 0x80, 1);
        if (padding_size > 8) {
          memcpy(block_unit + 55, &file_length_bit, 8);
        } else {
          memcpy(block_unit + 55, &file_length_bit, 8);
        }
      }
    } else {

    }

    memset(block_unit, 0, 64);
  }

  fclose(in);
  return 0;
 }