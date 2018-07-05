ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/obj
LIB_DIR = $(ROOT_DIR)/lib
TEST_DIR = $(ROOT_DIR)/test

CC = gcc
CC_FLAG = -std=c99 -Wall -Werror -g -I$(INC_DIR) -I$(LIB_DIR)



todo: $(OBJ_DIR)/main.o  $(OBJ_DIR)/todolist_model.o  $(OBJ_DIR)/todolist_storage.o  \
		$(OBJ_DIR)/todolist_service.o  $(OBJ_DIR)/todolist_console.o  $(LIB_DIR)/cJSON.o
	$(CC) $(CC_FLAG) $^ -lm -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c  $(INC_DIR)/todolist_model.h  \
	 	$(INC_DIR)/todolist_storage.h
	$(CC) $(CC_FLAG) -c $< -o $@


$(OBJ_DIR)/todolist_model.o: $(SRC_DIR)/todolist_model.c  $(INC_DIR)/todolist_model.h  \
		$(INC_DIR)/todolist_error_code.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/todolist_storage.o: $(SRC_DIR)/todolist_storage.c  $(INC_DIR)/todolist_storage.h  \
		$(INC_DIR)/todolist_error_code.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/todolist_service.o: $(SRC_DIR)/todolist_service.c  $(INC_DIR)/todolist_service.h  \
		$(INC_DIR)/todolist_error_code.h  $(INC_DIR)/todolist_model.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/todolist_console.o: $(SRC_DIR)/todolist_console.c  $(INC_DIR)/todolist_console.h  \
		$(INC_DIR)/todolist_console_const_val.h  $(INC_DIR)/todolist_service.h  \
		$(INC_DIR)/todolist_model.h  $(INC_DIR)/todolist_storage.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/cJSON.o:
	cd $(LIB_DIR) && make CC=$(CC)

$(INC_DIR)/*.h:
	touch *.h

test.out: $(OBJ_DIR)/main.o  $(OBJ_DIR)/todolist_model.o  $(OBJ_DIR)/todolist_storage.o  \
		$(OBJ_DIR)/todolist_service.o  $(OBJ_DIR)/todolist_console.o  $(LIB_DIR)/cJSON.o
	$(CC) $(CC_FLAG) $^ -lm -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o main *.out todo
