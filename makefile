# Copyright (C)  2016 jskyzero


ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
LIB_DIR = $(ROOT_DIR)/lib
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/build
BIN_DIR = $(ROOT_DIR)/bin

CC = gcc
FLAGS = -I $(ROOT_DIR) -I $(INC_DIR)



$(BIN_DIR)/SimpleCalculator: $(SRC_DIR)/SimpleCalculator.c $(OBJ_DIR)/ShellUI.o \
	$(OBJ_DIR)/Calculate.o
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_DIR)/ShellUI.o: $(SRC_DIR)/ShellUI.c
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(FLAGS) $^ -c -o $@

$(OBJ_DIR)/Calculate.o: $(SRC_DIR)/Calculate.c
	$(CC) $(FLAGS) $^ -c -o $@
 
clean:
	-rm -rf $(BIN_DIR)
	-rm -rf $(OBJ_DIR)