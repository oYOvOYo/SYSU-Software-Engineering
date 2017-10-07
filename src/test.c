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
  uint8_t key[8];
  read_key(argv[1], key);
  save_key(argv[2], key);
}