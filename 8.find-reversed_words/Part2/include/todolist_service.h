#ifndef TODOLIST_TODOLISTSERVICE_H__
#define TODOLIST_TODOLISTSERVICE_H__

#include "todolist_error_code.h"
#include "todolist_model.h"

error_t service_add_item(todolist_t* tdl, const char* content);
error_t service_finish_item(todolist_t* tdl, id_t item_id);

error_t service_find_item_by_id(const todolist_t* tdl, id_t item_id,
                                item_t** item);
error_t service_find_items_by_keyword(const todolist_t* tdl, const char* keyword,
                                      item_list_t** item_list);
int service_find_items_by_state(const todolist_t* tdl, item_list_t** item_list,
                                 int line_count, int is_done);

#endif // TODOLIST_TODOLISTSERVICE_H__