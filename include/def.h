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

#endif