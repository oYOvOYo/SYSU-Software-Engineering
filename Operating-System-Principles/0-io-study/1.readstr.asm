    SECTION .data
welcome_string  DB  "Welcome! "
welcome_length  EQU $-welcome_string
help_string     DB  "Please eneter your name: "
help_length     EQU $-help_string
read_string     times 2 DB 0
read_length     DB 2
; why set as 2 ? I want see the buffer is full and then
thanks_string   DB "thanks! "
thanks_length   EQU $-thanks_string


    SECTION .text
    global main

main:
print_welcome:
    mov eax, 4
    mov ebx, 1
    mov ecx, welcome_string
    mov edx, welcome_length
    int 0x80
print_help:
    mov eax, 4
    mov ebx, 1
    mov ecx, help_string
    mov edx, help_length
    int 0x80
read_name:
    mov eax, 3
    mov ebx, 0
    mov ecx, read_string
    mov edx, read_length
    int 0x80
print_thanks:
    mov eax, 4
    mov ebx, 1
    mov ecx, thanks_string
    mov edx, thanks_length
    int 0x80
    mov eax, 4
    mov ebx, 1
    mov ecx, read_string
    mov edx, read_length
    int 0x80
halt:
    mov eax, 1
    mov ebx, 0
    int 0x80