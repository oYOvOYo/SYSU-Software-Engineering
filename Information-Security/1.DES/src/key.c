/*
 *
 * key.c
 *
 * generate key use for des
 *
 * this key doesn't use addtional bit to check
 * just random produce number
 *
 * */

#include <key.h>

const uint8_t PERMUTED_CHOICE_1[] = {
    57, 49, 41, 33, 25, 17, 9,  1,  58, 50, 42, 34, 26, 18, 10, 2,  59, 51, 43,
    35, 27, 19, 11, 3,  60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7,  62, 54,
    46, 38, 30, 22, 14, 6,  61, 53, 45, 37, 29, 21, 13, 5,  28, 20, 12, 4};

const uint8_t PERMUTED_CHOICE_2[] = {
    14, 17, 11, 24, 1,  5,  3,  28, 15, 6,  21, 10, 23, 19, 12, 4,
    26, 8,  16, 7,  27, 20, 13, 2,  41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

// generate key
void generate_key(uint8_t* key) {
  srand(time(NULL));
  for (int i = 0; i < 8; i++) {
    key[i] = rand() % UINT8_MAX;
  }
}

// save key to file
void save_key(char* file_path, uint8_t* key) {
  FILE* out = fopen(file_path, "wb");
  check_file_open(out, file_path, "wb");

  for (int i = 0; i < 8; i++) {
    fprintf(out, "%c", key[i]);
  }

  fclose(out);
}

// read key from file
void read_key(char* file_path, uint8_t* key) {
  FILE* in = fopen(file_path, "rb");
  check_file_open(in, file_path, "rb");

  for (int i = 0; i < 8; i++) {
    if (fscanf(in, "%c", &key[i]) <= 0) exit(-1);
  }

  fclose(in);
}

// generate and then save it
void generate_and_sava_key(char* file_path) {
  uint8_t key[8];
  generate_key(key);
  save_key(file_path, key);
}

// generate sub key
void generate_sub_key(uint8_t* key, uint64_t* sub_keys) {
  uint64_t key64;
  uint8_to_uint64(key, &key64);
  map_uint64(&key64, PERMUTED_CHOICE_1, 56);
  uint64_t C = key64 & mask_uint64_from_to(0, 27);
  uint64_t D = (key64 & mask_uint64_from_to(28, 55)) >> 28;
  for (uint8_t i = 1; i <= 16; i++) {
    // loop shift
    switch (i) {
      case 1:
      case 2:
      case 9:
      case 16:
        C = ((C & mask_uint64_from_to(1, 27)) >> 1) |
            ((C & mask_uint64_from_to(0, 0)) << 28);
        D = ((D & mask_uint64_from_to(1, 27)) >> 1) |
            ((D & mask_uint64_from_to(0, 0)) << 28);
        break;
      default:
        C = ((C & mask_uint64_from_to(2, 27)) >> 2) |
            ((C & mask_uint64_from_to(0, 1)) << 27);
        D = ((D & mask_uint64_from_to(2, 27)) >> 2) |
            ((D & mask_uint64_from_to(0, 1)) << 27);
        break;
    }
    // compression
    key64 = C | (D << 28);
    map_uint64(&key64, PERMUTED_CHOICE_2, 48);
    sub_keys[i - 1] = key64 & mask_uint64_from_to(0, 47);
  }
}
