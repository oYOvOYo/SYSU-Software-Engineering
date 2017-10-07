# Copyright (C) 2017 jskyzero

ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
LIB_DIR = $(ROOT_DIR)/lib
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/build
BIN_DIR = $(ROOT_DIR)/bin
TEST_DIR = $(ROOT_DIR)/test

CC = gcc
FLAGS = -I $(ROOT_DIR) -I $(INC_DIR) -O3

$(BIN_DIR)/des: $(OBJ_DIR)/main.o $(OBJ_DIR)/key.o
	$(CC) $(FLAGS) $^ -o $@

# Makefile中的%标记和系统通配符*的区别
# http://www.cnblogs.com/warren-wong/p/3979270.html
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(FLAGS) $^ -c -o $@

clean:
	-rm -rf $(BIN_DIR)
	-rm -rf $(OBJ_DIR)