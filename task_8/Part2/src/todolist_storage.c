#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cJSON.h"
#include "todolist_storage.h"
#include "todolist_error_code.h"

error_t todolist_save(const todolist_t* tdl) {
    FILE* fout = fopen(DEFAULT_DATA_ADDRESS, "wt");

    if (!tdl || !fout) return FAILURE;

    /* Your code here. */

    fclose(fout);

    return SUCCESS;
}

error_t todolist_load(todolist_t* tdl) {
    FILE* fin = fopen(DEFAULT_DATA_ADDRESS, "rt");

    if (!tdl || !fin) return FAILURE;

    /* Your code here. */

    fclose(fin);

    return SUCCESS;
}