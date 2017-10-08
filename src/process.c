/*
 *
 * process.c
 *
 * main read/print part of des
 *
 *
 * */

#include <process.h>

// check whether file is open success
void process(PROCESS_TYPE process_type, char* key_file_path, char* in_file_path,
             char* out_file_path) {
  uint8_t key[8];
  uint8_t block_unit[8];
  uint64_t sub_Keys[16];

  read_key(key_file_path, key);
  generate_sub_key(key, sub_Keys);

  FILE* in = fopen(in_file_path, "rb");
  FILE* out = fopen(out_file_path, "wb");
  check_file_open(in, in_file_path, "rb");
  check_file_open(out, out_file_path, "wb");

  fseek(in, 0L, SEEK_END);
  long file_size = ftell(in);
  fseek(in, 0L, SEEK_SET);
  uint8_t last_block_size = file_size % 8;
  uint8_t padding_size = 8 - last_block_size;
  unsigned long total_block_num = file_size / 8 + (last_block_size > 0 ? 1 : 0);
  unsigned long now_read_block_num = 0;

  while (fread(block_unit, 1, 8, in)) {
    now_read_block_num++;

    if (now_read_block_num == total_block_num) {
      if (process_type == ENCRYPTION_MODE) {
        if (padding_size < 8) {
          memset(block_unit + 8 - padding_size,padding_size, padding_size);
        }
        process_unit(process_type, sub_Keys, block_unit);
        fwrite(block_unit, 1, 8, out);

        // add additional padding block
        if (padding_size == 8) {
          memset(block_unit, padding_size, 8);
          process_unit(process_type, sub_Keys, block_unit);
          fwrite(block_unit, 1, 8, out);
        }
      } else {
        process_unit(process_type, sub_Keys, block_unit);
        padding_size = block_unit[8 - 1];
        fwrite(block_unit, 1, 8 - padding_size, out);
      }
    } else {
     process_unit(process_type, sub_Keys, block_unit);
     fwrite(block_unit, 1, 8, out);
    }

    memset(block_unit, 0, 8);
  }


  fclose(in);
  fclose(out);
}