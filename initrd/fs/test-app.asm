mov edi, eax

mov eax, 0        ;; SYS_WRITE
mov ebx, hello
mov ecx, length
mov esi, 0x7b7b7b ;; A nice teal
int 37

mov eax, edi
ret

hello: db "Hello world!", 10, 0
length equ $ - hello