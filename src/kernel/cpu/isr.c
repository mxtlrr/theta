#include "cpu/isr.h"

// Gets the bad opcode at the IP.
// Adapted from my other project, mmlv.
uint32_t get_faulty_opcode(uint32_t ip){
	return (*(uint32_t*)ip) & 0xff;
}

/*
 31         16   15         3   2   1   0
+---+--  --+---+---+--  --+---+---+---+---+
|   Reserved   |    Index     |  Tbl  | E |
+---+--  --+---+---+--  --+---+---+---+---+ */
void analyze_gpf(uint32_t errcode){
	setcolor(0x00027d);
	printf("\nAnalysis:\n");
	if(errcode & (1<<0)) printf("This exception originated externally from processor\n");

	uint32_t tables = (errcode & (1<<1)) + (errcode & (1<<2));
	switch(tables){
		case 0b00:
			printf("Descriptor in GDT caused fault.\n");
			break;

		case 0b01:
			printf("Descriptor in IDT caused fault.\n");
			break;

		case 0b10:
			printf("Descriptor in LDT caused fault.\n");
			break;

		case 0b11:
			printf("Descriptor in IDT caused fault (binary 0b11)\n");
			break;
	}

	// Bits 3-15 are the selector
	printf("Index: %d (hex: %x)\n", (errcode >> 3) & 0x1FFF, (errcode >> 3) & 0x1FFF);
}

__attribute__((interrupt))
void exception_handler(registers_t* r){
  setcolor(0xFF0000);
  printf("Exception occurred at IP=%x:%x. (Opcode(s): %x %x)\n",
					r->cs, r->ip,
					get_faulty_opcode(r->ip), get_faulty_opcode(r->ip+1));

	printf("Interrupt number is %d (hex: %xh) [ec: %d]\n", r->int_no,
					r->int_no, r->errcode);

	// If the opcode is 0x0d (GPF) then we can analyze what actually
	// happened.
	if(r->int_no == 0x0d && r->errcode != 0) analyze_gpf(r->errcode);
  for(;;) __asm__("cli; hlt");
}



isr_t handlers[256];
void irq_handler(registers_t* r){
	
	// Acknowledge the interrupt, send an EOI.
	// Did the IRQ come from slave PIC? (Anything above IRQ7 [39])
	if(r->int_no >= 40){
		outb(0xa0,0x20);
	}
	outb(0x20, 0x20); // Also send EOI to master PIC.

	// Does the handler exist?
	if(handlers[r->int_no] != 0){
		// Yes! Go handle it.
		isr_t handler = handlers[r->int_no];
		handler(r);

		// When we come back we send an end-of-interrupt.
	}
}

// If an ISR is 0, then the handler does not exist, and we
// just "let it go"
void register_IRQ(uint8_t vector, isr_t callback){
	printf("Registered vector %x.\n", vector, callback);
	handlers[vector] = callback;
}



