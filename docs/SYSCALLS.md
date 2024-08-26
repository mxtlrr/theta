# Developer Guide -- Syscalls
When developing applications for theta, be it a graphing calculator,
or a simple hello world, you must somehow interact with the kernel.
This is where syscalls come into play. Theta uses `int 37` (IRQ5) for
this purpose.

Currently, there are 2:
- `sys_write`
- `sys_read`

The table below shows what each register is used for. N/A means that
that the register can have any value -- theta will ignore it.

| **Name**    | **EAX** |**EBX** | **ECX** | **ESI** | **EDI** |
| ----------- | ------- | ------ | ------- | ------- | ------- |
| sys_write   | `0x00`  | buffer | count   | color   | N/A     |
| sys_read    | `0x01`  | buffer | bytes   | N/A     | N/A     |
| fb_putpixel | `0x10`  | x pos  | y pos   | N/A     | N/A     |
| fb_setcolor | `0x11`  | N/A    | N/A     | color   | N/A     |

# Explanations

## I/O Syscalls

### `sys_write`
`sys_write` will ouput `count` bytes of `buffer` with color `color` onto
the framebuffer. Eventually there will be some API to plot a pixel. It should
be noted that `esi` is a 32-bit value with the format `0xRRGGBB`, so

> `mov esi, 0x00ff00`

will result in the text being printed with `RGB(0,255,0)`. A.K.A green.

### `sys_read`
`sys_read` will read n (n being value of `ecx`) bytes into the buffer
pointed to by `ebx`.

## Video Syscalls

### `fb_putpixel`
*WARNING: This syscall is a bit broken. This will need to be fixed later on.*

`fb_putpixel` uses the VRAM to plot a pixel at (EBX, ECX) with color ESI. For
example,
```x86asm
mov eax, 11h    ;; FB_PUTPIXEL
xor ebx, ebx
mov ecx, ebx
mov esi, 0xff0000
int 37
```

will plot a RED (`RGB(255,0,0)`) pixel at (0,0) on the screen.

### `fb_setcolor`
This syscall modifies an internal variable named `color`, which controls the
color of the output. `printf()` (internal) relies on this variable to output
in a specific color.