[bits 32]       ;; Allows for 32-bit registers to contain >0xffff
                ;; as a value
mov edi, eax    ;; Save EAX state, need for returning to caller

%macro reset_col 0
  mov eax, 0x11     ;; FB_SETCOLOR
  mov esi, 0xffffff
  int 37
%endmacro

%macro write_buf 3
  mov eax, 0
  mov ebx, %1
  mov ecx, %2
  mov esi, %3
  int 37
%endmacro

mov eax, 1
mov ebx, buffer
mov ecx, 11     ;; Read 10 bytes to buffer
int 37

;; Once we have that data, we should print it out.
write_buf buffer, 11, 0xff0000
reset_col
write_buf nl, 2, 0xffffff

mov eax, edi
ret

buffer: times 10 db 0
nl: db "", 0