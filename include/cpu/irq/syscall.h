#pragma once

#include <stdint.h>
#include <stddef.h>

#include "cpu/idt.h"
#include "cpu/isr.h"

#define SYS_WRITE 0
#define SYS_READ  1

void handle_syscall(registers_t* frame);
void initialize_syscalls(void);