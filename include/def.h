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

// process type
#define ENCRYPTION_MODE 1
#define DECRYPTION_MODE 0

// Declare action parameters
#define ACTION_GENERATE_KEY "-g"
#define ACTION_ENCRYPT "-e"
#define ACTION_DECRYPT "-d"

#endif