# The Makefile of the C vector in task 2.
# Copyright (c) 2016 sysu_AT. All righs reserved.

main: main.o c_vector.o
	gcc $^ -o $@

main.o: main.c
	gcc -std=c99 -Wall -Werror -c $< -o $@

# You had better remove the flag '-Wno-return-type'
c_vector.o: c_vector.c c_vector.h
	gcc -std=c99 -Wno-return-type -Wall -Werror -c $< -o $@

clean:
	rm -rf *.o test
