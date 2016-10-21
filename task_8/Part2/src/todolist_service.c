#include "todolist_service.h"
#include "todolist_model.h"
#include "todolist_error_code.h"

#include <string.h>
#include <time.h>
#include <assert.h>

static int filter_by_id(const item_t* item, va_list ap);
static int filter_by_keyword(const item_t* item, va_list ap);
static int filter_by_state(const item_t* item, va_list ap);

error_t service_add_item(todolist_t* tdl, const char* content) {
    if (!tdl) return FAILURE;
    return todolist_add_item(tdl, content, todolist_get_a_new_id(tdl), UNFINISHED,
                             time(NULL));
}

error_t service_finish_item(todolist_t* tdl, id_t item_id) {
    if (!tdl) return FAILURE;
    return todolist_finish_item(tdl, item_id, time(NULL));
}

static error_t service_find_item(const todolist_t* tdl, item_t** return_item,
                                 filter_t filter, ...) {
    assert(tdl && return_item);

    va_list ap;
    va_start(ap, filter);
    
    item_list_t* return_list = create_item_list();
    if (todolist_vfind_items(tdl, &return_list, filter, ap) == FAILURE)
        return FAILURE;
    assert(return_list->head && return_list->head == return_list->tail);
    destroy_item(return_item);
    *return_item = copy_item(return_list->head->data);

    destroy_item_list(&return_list);
    va_end(ap);
    
    return SUCCESS;
}


error_t service_find_items_by_keyword(const todolist_t* tdl, const char* keyword,
                                      item_list_t** item_list) {
    return todolist_find_items(tdl, item_list, filter_by_keyword, keyword);
}

error_t service_find_item_by_id(const todolist_t* tdl, id_t item_id,
                                item_t** item) {
    /* Your code here. */
}

int service_find_items_by_state(const todolist_t* tdl, item_list_t** item_list,
                                int line_count, int is_done) {
    item_state_t state = is_done ? FINISHED : UNFINISHED;

    item_list_t* tmp = create_item_list();
    todolist_find_items(tdl, &tmp, filter_by_state, state);

    const item_node_t* p = tmp->head;
    int count = 0;
    for (; count < line_count && p ; count++, p = item_node_next(p))
        item_list_add((*item_list), p->data);
    
    destroy_item_list(&tmp);
    return count;
}

static int filter_by_id(const item_t* item, va_list ap) {
    assert(item);
    int id = va_arg(ap, int);
    return item->id == id;
}

static int filter_by_keyword(const item_t* item, va_list ap) {
    assert(item);
    /* Your code here. */
}

static int filter_by_state(const item_t* item, va_list ap) {
    assert(item);
    item_state_t state = va_arg(ap, item_state_t);
    return item->state == state;
}
