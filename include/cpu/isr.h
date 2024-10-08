#pragma once

#include "video/stdio.h"
#include "cpu/idt.h"


#define IRQ_FROM_N(x) (x+32)

union Gdtr {
	uint8_t buffer[6];
	struct {
		uint16_t gdt_limit;
		void* gdt_base;
	} __attribute__((packed));
};

union Idtr {
	uint8_t buffer[6];
	struct {
		uint16_t idt_limit;
		void* idt_base;
	} __attribute__((packed));
};



__attribute__((noreturn))
void exception_handler(registers_t* r);



typedef void (*isr_t)(registers_t*);
void register_IRQ(uint8_t vector, isr_t callback);

