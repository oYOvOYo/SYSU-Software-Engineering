    SECTION .text
    global main
main:
    mov eax, 4
    mov ebx, 1
    mov ecx, BootMessage
    mov edx, BootMessageLength
    int 0x80

    mov eax, 1
    mov ebx, 0
    int 0x80

    SECTION .data
BootMessage:    DB "Welcome to Sky OS!"
BootMessageLength:  EQU $-BootMessage