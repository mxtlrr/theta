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
	switch(opcode){
		case 0xfa:
			return "cli";
			break;
		case 0xf4:
			return "hlt";
			break;
		case 0x61:
			return "popa";
			break;
		case 0x83:
			return "add";
			break;
		case 0xc4:
			return "register ESP";
			break;
		default:
			return "???";
			break;
	}
}

void DoStackTrace(uint32_t frames){
	struct stackframe* stk;
	__asm__("movl %%ebp, %0" : "=r"(stk) ::);
	printf("Stack trace (max 3 entries):\n");
	for(uint32_t curr = 0; stk && curr < frames; ++curr){
		// We should see what opcodes they are, since this is kinda
		// useless just to know WHAT it is.
		
		int opcodes[2] = { get_faulty_opcode(stk->eip),
												get_faulty_opcode(stk->eip+1) };
		printf("   0x%x [%x (%s) %x (%s)]\n", stk->eip,
						opcodes[0], get_opcode(opcodes[0]), opcodes[1],
						get_opcode(opcodes[1]));
		stk = stk->ebp;
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
	"Bad TSS       ",
	"No segment    ",
	"Stack-segment ",
	"General Prot  ",
	"Page Fault    ",
	"Reserved      ",
	"x87 FPU       ",
	"Alignment     ",
	"Machine Check ",
	"SIMD Exception"
};

__attribute__((interrupt))
void exception_handler(registers_t* r){
  setcolor(0xFF0000);

	// Ring number is in low 2 bits of Code Segment.
	uint32_t cpl = (r->cs & (1<<0)) + (r->cs & (1<<1));

	printf("!! EXCEPTION OCCURRED !!\n");
	printf("Name: %s\n", exceptions[r->int_no]);
	printf("%d: v=%x e=%x cpl=%d IP=%x:%x pc=%x\n",
				isr_count, r->int_no, r->errcode, cpl, r->cs, r->ip-1,
				r->ip-1);
	printf("EAX=%x EBX=%x ECX=%x EDX=%x\nESI=%x EDI=%x EBP=%x ESP=%x\n",
					r->eax, r->ebx, r->ecx, r->edx,
					r->esi, r->edi, r->ebp, r->esp);
	
	union Gdtr gdt;
	union Idtr idt;
	__asm__("sgdt %0" :"=m"(gdt.buffer));
	__asm__("sidt %0" :"=m"(idt.buffer));


	printf("GDT: %x %x\nIDT: %x %x\n", gdt.gdt_base, gdt.gdt_limit,
					idt.idt_base, idt.idt_limit);
	
	// Analyze error code given from GPF
	if(r->int_no == 0xd && r->errcode != 0) analyze_gpf(r->errcode);

	// Stack trace
	setcolor(0x820000);
	DoStackTrace(3);

	// Do not return. Halt computer
	for(;;) __asm__("cli//hlt");
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



