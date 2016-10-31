ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)
INC_DIR = $(ROOT_DIR)
LIB_DIR = $(ROOT_DIR)
OBJ_DIR = $(ROOT_DIR)
BIN_DIR = $(ROOT_DIR)

CC = g++
CC_FLAG = -std=c++11  -I$(INC_DIR)


main: $(SRC_DIR)/main.c $(SRC_DIR)/find_the_kth_largest_element.c \
		$(SRC_DIR)/find_the_kth_largest_element.cpp
	$(CC) $(CC_FLAG) $(SRC_DIR)/find_the_kth_largest_element.c \
		$(SRC_DIR)/main.c  -o $@

clean:
	rm -rf $*.o main

