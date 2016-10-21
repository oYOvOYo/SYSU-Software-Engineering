#include <assert.h> // for assert
#include <stdio.h> // for printf, getchar
#include <string.h> // for strcmp, strlen, strerror
#include <stdlib.h> // for strtol, malloc, free
#include <errno.h> // for errno

#include "todolist_console.h"
#include "todolist_console_const_val.h"
#include "todolist_service.h"
#include "todolist_model.h"
#include "todolist_storage.h"
#include "todolist_error_code.h"


/* it will free the memory */

static cmd_t get_command(const char* cmd);

static void print_error(const char* err);
static void print_info(const char* info);
static void print_usage(todolist_t* tdl, int argc, char* argv[]);

static int console_run_todolist(todolist_t* tdl, int argc, char* argv[]);
static void console_print_list_by_default(todolist_t* tdl);
static void console_print_list(todolist_t* tdl, int argc, char* argv[]);
static void console_add_item(todolist_t* tdl, int argc, char* argv[]);
static void console_finish_item(todolist_t* tdl, int argc, char* argv[]);
static void console_find_item(todolist_t* tdl, int argc, char* argv[]);

static void get_buffer_from_console(char** buffer, size_t* len);
static void console_output_list(todolist_t* tdl, int line_max, int is_done);
static void output_item_list(const item_list_t* item_list);
static void output_item(const item_t* item);


// Done
int todolist_console(int argc, char* argv[]) {
    todolist_t* tdl = create_todolist();

    if (todolist_load(tdl) == FAILURE)
        print_info("File initialization...");

    int result = console_run_todolist(tdl, argc, argv);

    todolist_save(tdl);
    destroy_todolist(&tdl);

    return result == SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
}

// Done
static error_t console_run_todolist(todolist_t* tdl, int argc, char* argv[]) {
    assert(tdl && argc > 0);

    cmd_t cmd = UNKNOWN_CMD;

    if (argc == 1) {
        cmd = NONE;
    } else {
        cmd = get_command(argv[1]);
    }
    
    switch (cmd) {
        case UNKNOWN_CMD: 
            print_usage(tdl, argc, argv); 
            break;
        case NONE: 
            console_print_list_by_default(tdl);
            break;
        case LIST: 
            console_print_list(tdl, argc, argv);
            break;
        case ADD: 
            console_add_item(tdl, argc, argv);
            break;
        case FINISH: 
            console_finish_item(tdl, argc, argv);
            break;
        case FIND: 
            console_find_item(tdl, argc, argv);
            break;
        default: 
            assert(0);
    }

    return SUCCESS; // should not be here
}


static cmd_t get_command(const char* cmd) {
    /* None, list, add, finish, find [, update, commit, rollback ] */
    if (strcmp(cmd, "list") == 0)
        return LIST;
    else if (strcmp(cmd, "add") == 0)
        return ADD;
    else if (strcmp(cmd, "finish") == 0)
        return FINISH;
    else if (strcmp(cmd, "find") == 0)
        return FIND;
    else
        return UNKNOWN_CMD;
}


static void print_usage(todolist_t* tdl, int argc, char* argv[]) {
    printf("Usage: todolist <command> [flag].\n");
}


static void console_print_list(todolist_t* tdl, int argc, char* argv[]) {
    assert(argc > 1);

    // config value
    int line_max = DEFAULT_PRINT_LINE_SIZE;

    for (int i = 2; i < argc; i++) {
        // line size
        if (strcmp(argv[i], PRINT_LINE_SIZE_FLAG_ABBR) == 0 ||
            strcmp(argv[i], PRINT_LINE_SIZE_FLAG) == 0) {

                if (i + 1 == argc) {
                    print_error("Expect a number of line.");
                    return;
                }

                char* end_ptr = NULL;
                int line_tmp = strtol(argv[i + 1], &end_ptr, 10);

                if (strlen(argv[i + 1]) == (end_ptr - argv[i + 1])) {
                    line_max = (line_max > line_tmp ? line_max : line_tmp);
                } else {
                    print_error("Expect a number of line.");
                    return;
                }
                i++;

        // unknown flags
        } else {
            print_error("unknown flags.");
            return;
        }
    }

    console_output_list(tdl, line_max, UNDO);
}


static void console_print_list_by_default(todolist_t* tdl) {
    console_output_list(tdl, DEFAULT_PRINT_LINE_SIZE, UNDO);
}


static void console_add_item(todolist_t* tdl, int argc, char* argv[]) {
    assert(argc > 1);

    char* content = NULL;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], ADD_ITEM_FLAG_ABBR) == 0 ||
            strcmp(argv[i], ADD_ITEM_FLAG) == 0) {

                if (i + 1 == argc) {
                    print_error("Expect a short sentence \"<str>\".");
                    return;
                }

                content = argv[i + 1];
                i++;

        // unknown flags
        } else {
            print_error("unknown flags.");
            return;
        }
    }

    int result = -1; // failed by default

    if (content == NULL) {
        size_t buffer_size = 512; // default
        content = (char*)malloc(buffer_size * sizeof(char));
        get_buffer_from_console(&content, &buffer_size); // it will call realloc
        result = service_add_item(tdl, content);
        free(content);
        content = NULL;
    } else {
        result = service_add_item(tdl, content);
    }

    if (result == SUCCESS) {
        print_info("Adding...Done!");
    } else {
        print_error("Adding...Failed!");
    }
}


static void console_finish_item(todolist_t* tdl, int argc, char* argv[]) {
    // 可以考虑增加扩展功能 通过关键词定位唯一的item直接finish.
    assert(argc > 1);

    char* end_ptr = NULL;
    int item_id = strtol(argv[2], &end_ptr, 10);
    
    if (strlen(argv[2]) != (end_ptr - argv[2])) {
        print_error("Expect a valid number of ID.");
    }

    if (service_finish_item(tdl, item_id) == SUCCESS) {
        print_info("Finished!");
    } else {
        print_error("Finish...Failed!");
    }
}


static void console_find_item(todolist_t* tdl, int argc, char* argv[]) {
    assert(argc > 1);

    int item_id = -1;
    int is_find_by_id = 0;

    const char* item_keyword = NULL;
    int is_find_by_keyword = 0;

    for (int i = 2; i < argc; i++) {
        if ((strcmp(argv[i], FIND_ITEM_BY_ID_FLAG_ABBR) == 0 ||
            strcmp(argv[i], FIND_ITEM_BY_ID_FLAG) == 0) &&
            !is_find_by_keyword) {
                char* end_ptr = NULL;
                item_id = strtol(argv[i + 1], &end_ptr, 10);
                
                if (strlen(argv[i + 1]) != (end_ptr - argv[i + 1])) {
                    print_error("Expect a valid number of ID.");
                    return;
                }
                is_find_by_id = 1;
                i++;

        // find by keyword
        } else if ((strcmp(argv[i], FIND_ITEM_BY_KEYWORD_FLAG_ABBR) == 0 ||
                   strcmp(argv[i], FIND_ITEM_BY_KEYWORD_FLAG) == 0) &&
                   !is_find_by_id) {
            item_keyword = argv[i + 1];
            is_find_by_keyword = 1;
            i++;

        // unknown flags
        } else {
            print_error("unknown flags.");
            return;
        }
    }


    error_t result = FAILURE;

    if (is_find_by_id) {
        item_t* item = create_empty_item();
        result = service_find_item_by_id(tdl, item_id, &item);
        output_item(item);
        destroy_item(&item);
    } else if (is_find_by_keyword) {
        item_list_t* item_list = create_item_list();
        
        /* Your code here. */

        output_item_list(item_list);
        destroy_item_list(&item_list);
    } else {
        assert(0);
    }

    if (result != FAILURE) {
        fprintf(stderr, "Failed to find.");
    }
}


static void console_output_list(todolist_t* tdl, int line_max, int is_done) {
    item_list_t* item_list = create_item_list(); // for traversal

    service_find_items_by_state(tdl, &item_list, line_max, is_done);

    output_item_list(item_list);

    destroy_item_list(&item_list);
}

static void output_item_list(const item_list_t* item_list) {
    const item_node_t* p = item_list->head;
    print_info("==========================================");
    while (p) {
        output_item(p->data);
        p = item_node_next(p);
    }
    print_info("==========================================");
}

static void output_item(const item_t* item) {
    const char* state_str = NULL;
    
    if (item->state == FINISHED)
        state_str = "Done";
    else if (item->state == UNFINISHED)
        state_str = "TODO";
    else
        state_str = "Unknown";

    // part of output in green font in command line
    fprintf(stdout, "\33[32m[%s]\33[0m[%d] %s\n", state_str, item->id, item->content);
}

static void get_buffer_from_console(char** buffer, size_t* len) {
    // When its size is not enough, it should realloc a double size memory
    // to store the string.
    assert(*len > 0);
    size_t k = 0;
    int c = EOF;
    while ((c = getchar()) != EOF) {
        (*buffer)[k++] = c;
        if (k - 1 == *len) {
            (*len) *= 2;
            (*buffer) = (char*)realloc(*buffer, (*len) * sizeof(char));
        }
    }
    (*buffer)[k] = '\0';
}

static void print_error(const char* err) {
    fprintf(stderr, "[Error] %s\n", err);
}
static void print_info(const char* info) {
    fprintf(stdout, "[Info] %s\n", info);
}
