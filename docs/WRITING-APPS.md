# Theta Application Development
When developing apps for theta, there are some things one must take into
account to prevent one (or more) of the following cases happening:
1. Code execution in places you *don't want it to be executing at*
2. Raising exceptions

## Storing `EAX` 
When an application is called from theta, it uses `EAX` to jump to the
binary:

*include/asm/exec_binary.asm:*
```x86asm
    ...
    mov eax, [esp+4]
    jmp eax
    ...
```

To prevent going off an executing random code, you must save EAX in
some register and restore it *before* you leave the program. For
example,

```x86asm
mov edi, eax

...

; Assuming EDI hasn't been modified.
; You can also use a label / variable for this.
mov eax, edi
ret
```
