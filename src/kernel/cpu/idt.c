#include "cpu/idt.h"

__attribute__((aligned(0x10)))
static idt_entry_t idt[256];
static idtr_t idtr;

static bool vectors[IDT_MAX_DESCRIPTORS];
extern void* isr_stub_table[];

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags){
  idt_entry_t* desc = &idt[vector];

  desc->isr_low    = (uint32_t)isr & 0xffff;
  desc->kcs        = CODESEG_KERNEL;
  desc->attributes = flags;
  desc->isr_high   = (uint32_t)isr >> 16;
  desc->reserved   = 0;
}

void idt_init() {
  idtr.base = (uintptr_t)&idt[0];
  idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

  for (uint8_t vector = 0; vector < 32; vector++) {
    idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    vectors[vector] = true;
  }

  // Load IDT and then enable interrupts
  __asm__ volatile ("lidt %0" : : "m"(idtr));
  __asm__ volatile ("sti");
}
