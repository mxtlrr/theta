#pragma once

#include "video/stdio.h"
#include "cpu/idt.h"


#define IRQ_FROM_N(x) (x+32)

__attribute__((interrupt))
void exception_handler(registers_t* r);



typedef void (*isr_t)(registers_t);
void register_IRQ(uint8_t vector, isr_t callback);

