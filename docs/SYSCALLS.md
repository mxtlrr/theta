# Developer Guide -- Syscalls
When developing applications for theta, be it a graphing calculator,
or a simple hello world, you must somehow interact with the kernel.
This is where syscalls come into play.

Currently, there are 2:
- `sys_write`
- `sys_read`

The table below shows what each register is used for. N/A means that
that the register can have any value -- theta will ignore it.

| **Name** | **EAX** |**EBX** | **ECX** | **ESI** | **EDI** |
| -        |-        | -      |-        |-        | -       |
| sys_write| 0       | buffer | count   | color   | N/A     |
| sys_read | 1       | buffer | bytes to read | N/A | N/A   |

# Explanations

## `sys_write`
`sys_write` will ouput `count` bytes of `buffer` with color `color` onto
the framebuffer. Eventually there will be some API to plot a pixel. It should
be noted that `esi` is a 32-bit value with the format `0xRRGGBB`, so

> `mov esi, 0x00ff00`

will result in the text being printed with `RGB(0,255,0)`. A.K.A green.

## `sys_read`
`sys_read` will read n (n being value of `ecx`) bytes into the buffer
pointed to by `ebx`.