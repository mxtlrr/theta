#include "cpu/irq/syscall.h"
#include "cpu/isr.h"

int isr_count = 0;

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
	setcolor(0x46a832);
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

char* get_opcode(uint8_t opcode){
	if(opcode < 10) return atoi(opcode, 10);
	switch(opcode){
		case 0xfa:
			return "cli";
		case 0xf4:
			return "hlt";
		case 0x61:
			return "popa";
		case 0x83:
			return "add";
		case 0xcd:
			return "int";
		case 0xc3:
			return "ret";
		case 0x90:
			return "nop";
		case 0xf9:
			return "stc";
		default:
			return "???";
	}
}

char* exceptions[] = {
	"Division      ",
	"Debug         ",
	"NMI           ",
	"Breakpoint    ",
	"Overflow      ",
	"Bound Range   ",
	"Bad Opcode    ",
	"No device     ",
	"Double Fault  ",
	"Reserved      ",
	"Bad TSS       ",
	"No segment    ",
	"Stack-segment ",
	"General Protection",
	"Page Fault    ",
	"Reserved      ",
	"x87 FPU       ",
	"Alignment     ",
	"Machine Check ",
	"SIMD Exception"
};

void exception_handler(registers_t* r){
	setcolor(0xffffff);
	for(;;) asm("cli//hlt");
}





isr_t handlers[256];
void irq_handler(registers_t* r){
	isr_count++;
	// Acknowledge the interrupt, send an EOI.
	if (r->int_no >= 40) outb(0xA0, 0x20);
	outb(0x20, 0x20);

	if (handlers[r->int_no] != 0) {
		handlers[r->int_no](r);
	}
	
}

// If an ISR is 0, then the handler does not exist, and we
// just "let it go"
void register_IRQ(uint8_t vector, isr_t callback){
	setcolor(0x00ff00);
	printf("Registered vector 0x%x (%d).\n", vector, vector, callback);
	setcolor(0xffffff);
	handlers[vector] = callback;
}



