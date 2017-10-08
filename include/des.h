/*
 *
 * des.h
 *
 * main unit process part of des
 *
 * */

// for uint8_t and other self define types
#include <def.h>
// for malloc
#include <string.h>

// process file
void process_unit(PROCESS_TYPE process_type, uint64_t* sub_keys, uint8_t* block_unit);