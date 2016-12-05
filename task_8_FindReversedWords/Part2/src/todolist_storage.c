#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen
#include <assert.h>
#include "cJSON.h"
#include "todolist_storage.h"
#include "todolist_error_code.h"



error_t todolist_save(const todolist_t* tdl) {
    FILE* fout = fopen(DEFAULT_DATA_ADDRESS, "wt");

    if (!tdl || !fout) return FAILURE;

    /* Your code here. */
    cJSON* root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "id_count", tdl->id_count);
    cJSON* item_list = cJSON_CreateArray();
    for (struct item_node* p = tdl->item_list->head; p != NULL; p = p->next) {
        cJSON* item = cJSON_CreateObject();
        cJSON_AddNumberToObject(item, "id", p->data->id);
        cJSON_AddStringToObject(item, "content", p->data->content);
        cJSON_AddNumberToObject(item, "state", p->data->state);
        cJSON_AddNumberToObject(item, "timestamp", p->data->timestamp);
        cJSON_AddItemToArray(item_list, item);
    }
    cJSON_AddItemToObject(root, "item_list", item_list);

    char* str = cJSON_Print(root);
    fwrite(str, sizeof(char), strlen(str), fout);

    cJSON_Delete(root);
    fclose(fout);

    return SUCCESS;
}

error_t todolist_load(todolist_t* tdl) {
    FILE* fin = fopen(DEFAULT_DATA_ADDRESS, "rt");

    if (!tdl || !fin) return FAILURE;

    /* Your code here. */
    fseek(fin, 0, SEEK_END);
	size_t file_size = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    char* str = (char*)malloc(sizeof(char) * (file_size+1));
    if (NULL == str) return FAILURE;
    size_t result = fread(str, 1, file_size, fin);
    if (result != file_size) return FAILURE;
    cJSON* root = cJSON_Parse(str);
    str[file_size] = '\0';
    free(str);

    if (root == NULL) return FAILURE;
    tdl->id_count = cJSON_GetObjectItem(root, "id_count")->valueint;
    cJSON* item_list = cJSON_GetObjectItem(root, "item_list");
    for (size_t i = 0; i < cJSON_GetArraySize(item_list); i++) {
        cJSON* item = cJSON_GetArrayItem(item_list, i);

        todolist_add_item(tdl, cJSON_GetObjectItem(item, "content")->valuestring,
                               cJSON_GetObjectItem(item, "id")->valueint,
                               cJSON_GetObjectItem(item, "state")->valueint,
                               cJSON_GetObjectItem(item, "timestamp")->valueint);
  }

    cJSON_Delete(root);
    fclose(fin);

    return SUCCESS;
}