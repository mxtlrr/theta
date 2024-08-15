gdt_start:
  gdt_null:
    dd 0
    dd 0

  gdt_code:
    dw 0xffff
    dw 0
    db 0
    db 0b10011010
    db 0b11001111
    db 0

  gdt_data:
    dw 0xffff
    dw 0
    db 0
    db 0b10010010
    db 0b11001111
    db 0
gdt_end:

gdtr:
  dw gdt_end - gdt_start - 1
  dd gdt_start

dataseg equ 0x10
codeseg equ 0x08

[global load_gdt]
load_gdt:
  lgdt [gdtr]

  ;; Fix segment selectors, so they aren't trashed
  ;; When we return
  mov ax, dataseg
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  jmp codeseg:.return
  .return:
    ret