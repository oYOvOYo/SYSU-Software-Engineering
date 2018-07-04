#ifndef TODOLIST_TODOLIST_STORAGE_H__
#define TODOLIST_TODOLIST_STORAGE_H__

#include "todolist_error_code.h"
#include "todolist_model.h"

#define DEFAULT_DATA_ADDRESS ".todolist_data"

error_t todolist_save(const todolist_t* tdl);
error_t todolist_load(todolist_t* tdl);

#endif // TODOLIST_TODOLIST_STORAGE_H__