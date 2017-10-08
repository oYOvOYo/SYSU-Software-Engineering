/*
 *
 * key.h 
 * 
 * include some header files for key.c
 * 
 * 
 * */


// for time
#include <time.h>
// for rand
#include <stdlib.h>
// for FILE, fopen, fclose, fprintf, fscanf
#include <stdio.h>

// for uint8_t and other self define types
#include <def.h>


// generate key
void generate_key(uint8_t* key);

// save key to file
void save_key(char* file_path, uint8_t* key);

// read key from file
void read_key(char* file_path, uint8_t* key);

// generate and then save it
void generate_and_sava_key(char* file_path);

// generate sub key
void generate_sub_key(uint8_t* key, uint64_t sub_keys);