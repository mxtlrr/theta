#include "cpu/irq/syscall.h"
#include "cpu/isr.h"

#define KTH_BIT_SET(n,k) ((n & (1<<k)) == 0)
#define XCR0_ACCESS_BIT 18

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
		case 0xcc:
			return "int3";
		case 0x58:
			return "pop eax";
		case 0x5a:
			return "pop edx";
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
	"Division",
	"Debug",
	"Non-Maskable",
	"Breakpoint",
	"Overflow",
	"Bound Range",
	"Invalid Opcode",
	"Unavailable Device",
	"Double Fault",
	"Reserved",
	"Invalid TSS",
	"Non-present segment",
	"Stack-segment fault",
	"General Protection Fault",
	"Page Fault",
	"Reserved",
	"x87 Floating-Point Exception",
	"Alignment Check",
	"Machine Check",
	"SIMD Exception"
};

void exception_handler(registers_t* r){
	setcolor(0xff0000);

	// 1: Dump register data
	printf("%d: v=%x (%s) IP=%x:%x pc=%x\n", isr_count, r->int_no,
			exceptions[r->int_no], r->cs, (r->ip-1), (r->ip-1));
	printf("EAX=%x EBX=%x ECX=%x EDX=%x\nESI=%x EDI=%x EBP=%x\n",
			r->eax, r->ebx, r->ecx, r->edx, r->esi, r->edi, r->ebp);

	// 2: Get GDT/IDT information
	union Gdtr gdt;
	union Idtr idt;
	__asm__("sgdt %0" :"=m"(gdt.buffer));
	__asm__("sidt %0" :"=m"(idt.buffer));
	printf("   GDT ==> 0x%x (base) 0x%x (limit)\n", gdt.gdt_base, gdt.gdt_limit);
	printf("   IDT ==> 0x%x (base) 0x%x (limit)\n", idt.idt_base, idt.idt_limit);


	// 3: Get CR0 and SSE registers.
	/// 3.1 CR0
	uint32_t cr0; uint32_t cr2; uint32_t cr3;
	uint64_t cr4;
	__asm__("smsw %%eax//mov %0, %%eax" :"=r"(cr0));
	__asm__("mov %%cr2, %0" :"=r"(cr2));
	__asm__("mov %%cr3, %0" :"=r"(cr3));

	// Get CR4 -- Which has alot of important stuff we want.
	__asm__("movl %%cr4, %0" :"=r"(cr4) ::);

	printf("CR0=%x CR2=%x CR3=%x CR4=%x\n",
				cr0, cr2, cr3, cr4);

	/// 3.2 SSE

	// 4: Get opcodes
	printf("\nOpcodes at/near exception:\n");
	setcolor(0x8c0900);
	for(uint32_t op = (r->ip-3); op != (r->ip+3);	op++){
		uint32_t opcode = get_faulty_opcode(op);
		if(op == r->ip-1) printf(" -> %x: %x [%s]\n", op, opcode, get_opcode(opcode));
		else printf("    %x: %x [%s]\n", op, opcode, get_opcode(opcode));
	}

	// 5: Analyze GPF
	if(r->int_no == 0xd && r->errcode > 0) analyze_gpf(r->errcode);
	setcolor(0xFFFFFF);
	printf("Halting your computer...");
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

char* irq_regs[] = {
	"PIT Timer",
	"Keyboard Handler",
	"Reserved",
	"Resvered",
	"Reserved",
	"Syscalls"
};

// If an ISR is 0, then the handler does not exist, and we
// just "let it go"
void register_IRQ(uint8_t vector, isr_t callback){
	printf("[ OK ] Enabled %s.\n", irq_regs[vector-32]);
	handlers[vector] = callback;
}



