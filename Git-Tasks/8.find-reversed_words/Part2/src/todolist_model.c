#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "todolist_model.h"


static item_t* todolist_get_item_reference(const todolist_t* tdl, id_t id);

/* Methods for Class Item */
item_t* create_item(const char* content, id_t id,
                 item_state_t state, time_t timestamp) {
    item_t* new_item = (item_t*)malloc(sizeof(item_t));
    assert(new_item); // create failed

    new_item->content = (char*)malloc((strlen(content) + 1) * sizeof(char));
    strcpy(new_item->content, content);
    new_item->id = id;
    new_item->state = state;
    new_item->timestamp = timestamp;

    return new_item;
}

item_t* create_empty_item() {
    item_t* new_item = (item_t*)malloc(sizeof(item_t));
    assert(new_item); // create failed

    new_item->content = NULL;
    new_item->id = 0;
    new_item->state = UNKNOWN_ITEM_STATE;
    new_item->timestamp = 0;
    
    return new_item;
}

void destroy_item(item_t** item) {
    if (!item || !*item) return;

    free((*item)->content);
    (*item)->content = NULL;
    free(*item);
    *item = NULL;
}

item_t* copy_item(const item_t* item) {
    item_t* new_item = (item_t*)malloc(sizeof(item_t));
    assert(item && new_item); // copy failed
    
    new_item->content = (char*)malloc((strlen(item->content) + 1) * sizeof(char));
    strcpy(new_item->content, item->content);
    new_item->id = item->id;
    new_item->state = item->state;
    new_item->timestamp = item->timestamp;

    return new_item;
}

const item_node_t* item_node_next(const item_node_t* item_node) {
    return item_node->next;
}

/* Methods for Class Item List */
item_list_t* create_item_list() {
    item_list_t* new_item_list = (item_list_t*)malloc(sizeof(item_list_t));
    assert(new_item_list); // create failed

    new_item_list->head = NULL;
    new_item_list->tail = NULL;

    return new_item_list;
}

void destroy_item_list(item_list_t** item_list) {
    if (!item_list && !*item_list) return;

    item_node_t* p = (*item_list)->head;
    while (p) {
        item_node_t* tmp = p;
        p = p->next;
        destroy_item(&(tmp->data));
        free(tmp);
        tmp = NULL;
    }

    free(*item_list);
    *item_list = NULL;
}

item_list_t* copy_item_list(const item_list_t* item_list) {
    item_list_t* new_item_list = create_item_list();
    assert(new_item_list);

    item_node_t* p = item_list->tail;
    while (p) {
        item_list_add(new_item_list, p->data);
        p = p->prev;
    }
    
    return new_item_list;
}

error_t item_list_add(item_list_t* item_list, const item_t* item) {
    if (!item_list || !item) return FAILURE;

    item_t* new_item = copy_item(item);
    assert(new_item);
    item_node_t* new_node = (item_node_t*)malloc(sizeof(item_node_t));
    assert(new_node);

    new_node->data = new_item;

    assert(!((item_list->head == NULL) ^ (item_list->tail == NULL)));
    item_node_t* p = item_list->tail;
    if (p) {
        item_node_t* tmp = p->next;
        p->next = new_node;
        new_node->prev = p;
        new_node->next = tmp;
        item_list->tail = new_node;
    } else {
        new_node->next = NULL;
        new_node->prev = NULL;
        item_list->head = item_list->tail = new_node;
    }
    
    return SUCCESS;
}

/* Methods for Class Todolist */

todolist_t* create_todolist() {
    todolist_t* new_tdl = (todolist_t*)malloc(sizeof(todolist_t));
    assert(new_tdl);

    new_tdl->id_count = 0;
    new_tdl->item_list = create_item_list();

    return new_tdl;
}

void destroy_todolist(todolist_t** tdl) {
    if (!tdl || !*tdl) return;

    destroy_item_list(&((*tdl)->item_list));

    free(*tdl);
    *tdl = NULL;
}

todolist_t* copy_todolist(const todolist_t* tdl) {
    todolist_t* new_tdl = create_todolist();
    assert(new_tdl);

    new_tdl->id_count = tdl->id_count;
    destroy_item_list(&new_tdl->item_list);
    new_tdl->item_list = copy_item_list(tdl->item_list);

    return new_tdl;
}

error_t todolist_add_item(todolist_t* tdl, const char* content, id_t id,
                          item_state_t state, time_t timestamp) {
    item_t* item = create_item(content, id, state, timestamp);
    if (!item || !tdl) return FAILURE;

    error_t result = item_list_add(tdl->item_list, item);

    return result;
}

error_t todolist_finish_item(todolist_t* tdl, id_t id, time_t timestamp) {
    if (!tdl) return FAILURE;

    item_t* item = todolist_get_item_reference(tdl, id);
    assert(item);
    item->state = FINISHED;
    item->timestamp = timestamp;

    return SUCCESS;
}

error_t todolist_find_items(const todolist_t* tdl, item_list_t** return_list,
                              filter_t filter, ...) {
    if (!tdl) return FAILURE;
    assert(return_list && *return_list && tdl->item_list);

    va_list ap;
    va_start(ap, filter);

    error_t result = todolist_vfind_items(tdl, return_list, filter, ap);

    va_end(ap);
    return result;
}

error_t todolist_vfind_items(const todolist_t* tdl, item_list_t** return_list,
                           filter_t filter, va_list ap) {
    if (!tdl) return FAILURE;
    assert(return_list && *return_list && tdl->item_list);

    item_node_t* p = tdl->item_list->head;
    while (p) {
        va_list vl;
        va_copy(vl, ap);
        if (filter(p->data, vl))
            item_list_add(*return_list, p->data);
        va_end(vl);
        p = p->next;
    }

    return SUCCESS;
}

id_t todolist_get_a_new_id(todolist_t* tdl) {
    return ++(tdl->id_count);
}

static item_t* todolist_get_item_reference(const todolist_t* tdl, id_t id) {
    if (!tdl) return NULL;
    item_node_t* p = tdl->item_list->head;
    while (p) {
        if (p->data->id == id)
            return p->data;
        p = p->next;
    }
    return NULL;
}