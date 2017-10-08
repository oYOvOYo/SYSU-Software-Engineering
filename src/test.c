/*
 *
 * test.c 
 * 
 * test some function
 * 
 * 
 * */

#include <test.h>

int main(int argc, char* argv[]) {
  uint8_t key[8], new_key[8];
  uint64_t key64;

  read_key(argv[1], key);

  uint8_to_uint64(key, &key64);
  uint64_to_uint8(&key64, new_key);

  save_key(argv[2], new_key);
}