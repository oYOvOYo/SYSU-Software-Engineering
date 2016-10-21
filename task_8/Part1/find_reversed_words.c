// Copyright (c) 2016 jskyzero. All righs reserved.
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <string.h> // for strlen


char* reverse_str(char* str) {
    size_t str_len = strlen(str) -1;
    for (int n = 0; n < str_len/2; n++) {
        char temp_char = str[n];
        str[n] = str[str_len - n -1];
        str[str_len - n -1] = temp_char;
    }
    return str;
}

int main() {
    FILE* read = fopen("words", "rt");
    FILE* write = fopen("result_c", "wt");
    char lines[100000][30] = {'\0'};
    char line[30]= {'\0'};
    if (read == NULL) {
        printf("%s", "orz");
        return -1;
    }

    for (int i = 0; i < 100000; i++) {
        fgets(lines[i], 30, read);
        if(feof(read)) break;
    }
    for (int i = 0; i < 100000; i++) {
        if (lines[i][0] == '\0') break;
        strcpy(line, lines[i]);
        reverse_str(line);
        for (int j = 0; j < 100000; j++) {
            if (lines[i][0] == '\0') break;
            if (0 == strcmp(line, lines[j])) {
                fputs(lines[i], write);
                break;
            }
        }
    }


    fclose(read);
    fclose(write);
    return 0;
}







// typedef char* value_type;
// typedef struct ListNode* node_ptr;

// typedef struct ListNode{
//     value_type value;
//     node_ptr next_node;
// } node_type;

// typedef struct {
//     node_ptr node;
// }List;

// List* list_create(List** list_ptr) {
//     List* temp_list = (List*)malloc(sizeof(List));
//     temp_list->node = NULL;

//     if (NULL != list_ptr) {
//         *list_ptr = temp_list;
//     }
//     return temp_list;
// }

// void list_push_back(List* list, value_type value) {
//     node_ptr new_node_ptr = (node_ptr)malloc(sizeof(node_type));
//     new_node_ptr->value = value;
//     new_node_ptr->next_node = NULL;

//     if (list->node == NULL) {
//         list->node = new_node_ptr;
//         return;
//     } else {
//         node_ptr temp_node_ptr = list->node;
//         for (temp_node_ptr; temp_node_ptr->next_node != NULL;
//                 temp_node_ptr = temp_node_ptr->next_node);
//         temp_node_ptr->next_node =new_node_ptr;
//     }

// }

// int list_check(List* list, value_type value) {
//     node_ptr p = NULL;
//     for ( p = list->node; p != NULL; p = p->next_node){
//          if (*value == *p->value)
//             return 1;
//     }
//     return 0;
// }




// int main() {
//     FILE* read = fopen("words", "rt");
//     FILE* write = fopen("result_c", "wt");
//     List* list;
//     list_create(&list);


//     if (read == NULL) {
//         printf("%s", "orz");
//         return -1;
//     }

//     while (!feof(read)) {
//         char* line_str = (char*)malloc(sizeof(char)*30);
//         fgets(line_str, 30, read);
//         if(feof(read)) break;
//         list_push_back(list, line_str);
//     }

//     node_ptr p = NULL;
//     for ( p = list->node; p != NULL; p = p->next_node){
//         char* line_str = (char*)malloc(sizeof(char)*30);
//         strcpy(line_str, p->value);
//         if (list_check(list, reverse_str(line_str)))
//             fputs(reverse_str(line_str), write);
//             printf("%s\n",line_str);
//     }

//     fclose(read);
//     fclose(write);
//     return 0;

// }

