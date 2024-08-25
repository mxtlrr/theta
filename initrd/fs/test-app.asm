mov edi, eax
xor eax, eax

mov eax, 0x11
mov esi, 0x7b7b7b
int 37

mov eax, 0x10
mov ebx, 10
mov ecx, 10
int 37

mov eax, edi
ret

