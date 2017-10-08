# Copyright (C) 2017 jskyzero

ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
LIB_DIR = $(ROOT_DIR)/lib
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/build
BIN_DIR = $(ROOT_DIR)/bin
TEST_DIR = $(ROOT_DIR)/test

CC = gcc
FLAGS = -I $(ROOT_DIR) -I $(INC_DIR) -O3 -std=c11
# FLAGS = -I $(ROOT_DIR) -I $(INC_DIR) -g -std=c11


all: mkdir $(BIN_DIR)/des

$(BIN_DIR)/des: $(OBJ_DIR)/main.o $(OBJ_DIR)/key.o $(OBJ_DIR)/def.o $(OBJ_DIR)/process.o
	$(CC) $(FLAGS) $^ -o $@

$(BIN_DIR)/test: $(OBJ_DIR)/test.o $(OBJ_DIR)/key.o $(OBJ_DIR)/def.o $(OBJ_DIR)/process.o
	$(CC) $(FLAGS) $^ -o $@

test: all $(BIN_DIR)/test
	# test key is same
	$(BIN_DIR)/des -g $(TEST_DIR)/test.key
	$(BIN_DIR)/test $(TEST_DIR)/test.key $(TEST_DIR)/test.key.new
	diff $(TEST_DIR)/test.key $(TEST_DIR)/test.key.new > /dev/null || \
	(echo "Test $@ failed" && exit 1)
	# test file is same
	./bin/des -e $(TEST_DIR)/test.key $(TEST_DIR)/example $(TEST_DIR)/test.example.enc
	./bin/des -d $(TEST_DIR)/test.key $(TEST_DIR)/test.example.enc $(TEST_DIR)/test.example.new
	diff $(TEST_DIR)/test.example.new $(TEST_DIR)/example > /dev/null || \
	(echo "Test $@ failed" && exit 1)


# Makefile中的%标记和系统通配符*的区别
# http://www.cnblogs.com/warren-wong/p/3979270.html
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $^ -c -o $@

mkdir:
	mkdir -p $(TEST_DIR) $(OBJ_DIR) $(BIN_DIR)

clean:
	-rm -rf $(BIN_DIR)
	-rm -rf $(OBJ_DIR)