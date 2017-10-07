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

#include<key.h>

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

  for (int i = 0; i < 8; i++) {
    fprintf(out, "%c", key[i]);
  }

  fclose(out);
}

// read key from file
void read_key(char * file_path, uint8_t* key) {
  FILE* in = fopen(file_path, "rb");

  for (int i = 0; i < 8; i++) {
    if (fscanf(in, "%c", &key[i]) <= 0)
      exit(-1);
  }

  fclose(in);
}

// generate and then save it
void generate_and_sava_key(char* file_path) {
  uint8_t key[8];
  generate_key(key);
  save_key(file_path, key);
}
