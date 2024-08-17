#include "cpu/isr.h"

// Gets the bad opcode at the IP.
// Adapted from my other project, mmlv.
uint32_t get_faulty_opcode(uint32_t ip){
	return (*(uint32_t*)ip) & 0xff;
}

__attribute__((interrupt))
void exception_handler(registers_t* r){
  setcolor(0xFF0000);
  printf("Exception occurred at IP=%x. (Opcode(s): %x %x)\n", r->ip,
					get_faulty_opcode(r->ip), get_faulty_opcode(r->ip+1));
  for(;;) __asm__("cli; hlt");
}
