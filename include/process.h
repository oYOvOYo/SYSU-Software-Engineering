/*
 *
 * process.h
 *
 * header file of process.c
 *
 *
 * */

// for FILE, fopen, fclose, fprintf, fscanf
#include <stdio.h>
 
// for uint8_t and other self define types
#include <def.h>
// for key part
#include <key.h>

// process file
void process(PROCESS_TYPE process_type, char* key_file_path, char* in_file_path,
             char* out_file_path);