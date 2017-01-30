# Copyright (C)  2016 jskyzero


ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
LIB_DIR = $(ROOT_DIR)/lib
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/build
BIN_DIR = $(ROOT_DIR)/bin
TEST_DIR = $(ROOT_DIR)/test

CC = gcc
FLAGS = -I $(ROOT_DIR) -I $(INC_DIR)



$(BIN_DIR)/SimpleCalculator: $(SRC_DIR)/SimpleCalculator.c $(OBJ_DIR)/shellUI.o \
	$(OBJ_DIR)/calculate.o $(OBJ_DIR)/error.o $(OBJ_DIR)/test.o \
	$(OBJ_DIR)/arithmetic.o
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_DIR)/shellUI.o: $(SRC_DIR)/shellUI.c
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(FLAGS) $^ -c -o $@

$(OBJ_DIR)/calculate.o: $(SRC_DIR)/calculate.c
	$(CC) $(FLAGS) $^ -c -o $@

$(OBJ_DIR)/error.o: $(SRC_DIR)/error.c
	$(CC) $(FLAGS) $^ -c -o $@

$(OBJ_DIR)/test.o: $(SRC_DIR)/test.c
	$(CC) $(FLAGS) $^ -c -o $@

$(OBJ_DIR)/arithmetic.o: $(SRC_DIR)/arithmetic.c
	$(CC) $(FLAGS) $^ -c -o $@

test: $(BIN_DIR)/SimpleCalculator
	less $(TEST_DIR)/test | ./$(BIN_DIR)/SimpleCalculator > $(TEST_DIR)/output
	diff $(TEST_DIR)/sample_output $(TEST_DIR)/output > /dev/null || \
	(echo "Test $@ failed" && exit 1)
clean:
	-rm -rf $(BIN_DIR)
	-rm -rf $(OBJ_DIR)
