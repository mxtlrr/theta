#pragma once

#include "video/stdio.h"
#include "cpu/idt.h"

__attribute__((interrupt))
void exception_handler(registers_t* r);
