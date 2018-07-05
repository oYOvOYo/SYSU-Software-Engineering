; This will be first x86 assembly code written by you.
; so we introduce this code and structure shortly
; first let's make it run
; we use linux bash and install nasm and gcc, then enter
;
;   nasm -f elf64 0.hello.asm -o hello.o
;   gcc hello.o -o hello
;   ./hello
;
; you will see in screen it print Helloworld!
; as about how to use nasm and gcc you can find more in website

; then let's talk about code structure 
; this is data and text section 
; (OK I know the names are not case-sensitive. but I like good code style)
; data is some data, text is some code

    SECTION .data
msg DB "Helloworld!" ; DB means Define Byte. 8 bits, DW(word generally 2 byte) DD(double word)
len EQU $-msg        ; EQU mens define constants

    SECTION .text
    global main      ; use label main

main:
    mov eax, 4       ; this part is a system call
    mov ebx, 1
    mov ecx, msg
    mov edx, len
    int 0x80         ; call

    mov eax, 1
    mov ebx, 0
    int 0x80         ; halt