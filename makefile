# Copyright (C) 2017 jskyzero

ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
LIB_DIR = $(ROOT_DIR)/lib
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/build
BIN_DIR = $(ROOT_DIR)/bin
TEST_DIR = $(ROOT_DIR)/test

CC = gcc
FLAGS = -I $(ROOT_DIR) -I $(INC_DIR)

$(BIN_DIR)/des: $(OBJ_DIR)/main.o
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(FLAGS) $^ -c -o $@

clean:
	-rm -rf $(BIN_DIR)
	-rm -rf $(OBJ_DIR)