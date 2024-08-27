#pragma once

#include <stdint.h>
#include <stddef.h>

#include "cpu/idt.h"
#include "cpu/isr.h"

#define SYS_WRITE 0
#define SYS_WRITE_NL 0xa
#define SYS_READ  1

#define FB_PLOTPIXEL 0x10
#define FB_SETCOLOR  0x11


void handle_syscall(registers_t* frame);
void initialize_syscalls(void);
