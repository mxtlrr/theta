#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "io.h"

#define CODESEG_KERNEL 0x08
#define IDT_MAX_DESCRIPTORS 256

typedef struct {
  uint16_t isr_low;
  uint16_t kcs;
  uint8_t  reserved;
  uint8_t  attributes;
  uint16_t isr_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

// Registers for interrupt handlers.
typedef struct {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	// https://wiki.osdev.org/Interrupt_Service_Routines
	uint32_t int_no, errcode;
	uint32_t ip, cs, eflags, useless, ss;
} registers_t;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);
