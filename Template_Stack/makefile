# make test for stack_s.h
main: main.o
	gcc $< -o $@

main.o: main.c  stack_s.h
	gcc -std=c99 -c -Wall -Werror $< -o $@ 

test_stack_s.o: test_stack_s.cpp  stack_s.h
	g++ -std=c++11 -Wall -Werror -c $< -o $@

test: test_stack_s.o /usr/lib/libgtest.a
	g++ -pthread -I/usr/bin/include $^ -o $@

clean:
	rm -rf *.o test main