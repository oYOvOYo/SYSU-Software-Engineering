; helloworld.asm a first program for nasm for Linux, Intel, gcc
;
; assemble: nasm -f elf64 helloworld.asm -o hello.o
;   Q:why is elf64?
;   A:use whre nasm find where is nasm and then use file /path/nasm you will find ELF 64-bit
;
; link:     gcc -o hello hello.o
;
; run:      ./hello
;
; outout:   HelloWorld!

    SECTION .data
msg: db "HelloWorld!"   ; data section 
len: equ $-msg          ; the string to print, 10=cr

    SECTION .text       ; code section
    global main         ; make lable available to linker 

main:
    mov edx, len        ; arg3, length of string to print 
    mov ecx, msg        ; arg2, pointer to string
    mov ebx, 1          ; arg1, where to write screen
    mov eax, 4          ; write command to int 80 hex
    int 0x80            ; interrupt 80 hex, call kernel

    mov ebx, 0          ; exit code, 0=normal
    mov eax, 1          ; exit command to kernal
    int 0x80            ; interrupt 80 hex, call kernel