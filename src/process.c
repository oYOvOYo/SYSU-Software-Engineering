/*
 *
 * process.c
 * 
 * main part of des
 * 
 * 
 * */

#include <process.h>

// check whether file is open success
void process(PROCESS_TYPE process_type, char* key_file_path, 
             char* in_file_path, char* out_file_path) {
  uint8_t key[8];
  uint64_t block_unint;

  FILE* in = fopen(in_file_path, "rb");
  FILE* out = fopen(out_file_path, "wb");
  check_file_open(in, in_file_path, "rb");
  check_file_open(out, out_file_path, "wb");

  fclose(in);
  fclose(out);
}