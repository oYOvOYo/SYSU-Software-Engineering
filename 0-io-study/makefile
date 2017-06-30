hello: hello.o
	gcc hello.o -o hello
hello.o:
	nasm -f elf64 1.readstr.asm -o hello.o
	# nasm -f elf64 test.asm -o hello.o
	# nasm -f elf64 1.read.asm -o hello.o

clean:
	rm *.o
	rm hello