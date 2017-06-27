    org 07c00h      ;告诉编译器程序加载到7c00处
    ; org 0100h
    mov ax, cs
    mov ds, ax
    mov es, ax
    call DispStr
    jmp $

DispStr:
    mov ax, BootMessage
    mov bp, ax      ;ex:bp = 串地址
    mov cx, 25      ;cx    = 串长度
    mov ax, 01301h  ;ah = 13, al = 01h
    mov bx, 000ch   ;页号为0（bh=0）黑底红字（bl = 0Ch，高亮）
    mov dl, 0
    int 10h
    ret
BootMessage:    db "HelloWorld! by jskyzero"
times 510-($-$$) db 0   ;填充剩余空间

dw 0xaa55