#include "cpu/idt.h"
#include "io.h"

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

// Remaps PIC. Master offset is at 0x20 and slave offset at 0x28
void remap_pic(){
	// Save masks -- we restore them later
	uint8_t a1, a2;
	a1 = inb(0x21);
	a2 = inb(0xa1);

	// Start initialization mode
	outb(0x20, 0x10 | 0x01);
	outb(0xa0, 0x10 | 0x01);

	// Send offsets to both master and slave
	outb(0x21, 0x20);
	outb(0xa1, 0x28);

	// Master, there's a slave at IRQ2!
	outb(0x21, 4);
	outb(0xa1, 2); // Cascade idenitity

	outb(0x21, 0x01); // Use 8086!
	outb(0xa1, 0x01);

	// Restore masks
	outb(0x21, a1);
	outb(0xa1, a2);
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

	// Remap PIC so that we do not use the BIOS defaults.
	// BIOS uses INT=0x08 for the PIT, but we set that up to be
	// the Double Fault handler, so it raises an exception (not good)
	remap_pic();
	// Now, we shouldn't get an exception when we load interrupts.
  __asm__ volatile ("sti");

	// The next thing I need to do is enable IRQs.
}
