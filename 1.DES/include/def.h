/*
 *
 * def.h
 *
 * this file contains typedef types and enum types
 *
 *
 * */

#ifndef _DEF_H_
#define _DEF_H_

// for uint8_t
#include <stdint.h>
// for File
#include <stdio.h>
// for exit
#include <stdlib.h>
// for memcpy
#include <string.h>

// process type
typedef enum {
  DECRYPTION_MODE = 0,
  ENCRYPTION_MODE = 1,
  UNDEFINED_MODE = 3
} PROCESS_TYPE;

// Declare action parameters
#define ACTION_GENERATE_KEY "-g"
#define ACTION_ENCRYPT "-e"
#define ACTION_DECRYPT "-d"

// const value
#define UNIT_SIZE 8



// check whether file is open success
void check_file_open(FILE* file, char* file_path, char* mode);
// convert uint8 to uint64
void uint8_to_uint64(uint8_t* array, uint64_t* num);
// convert uint64 to uint8
void uint64_to_uint8(uint64_t* num, uint8_t* array);

// map bit of uint64
void map_uint64(uint64_t* num, const uint8_t* table, uint8_t length);

// procude each bit mask from 0 bit to 63 bit
uint64_t mask_uint64(uint8_t index);
// procude mask from 0 bit to 63 bit
uint64_t mask_uint64_from_to(uint8_t begin, uint8_t end);

#endif