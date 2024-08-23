#include "cpu/irq/syscall.h"

void handle_syscall(registers_t* frame){
  printf("RECIEVED SYSCALL!\n");
  printf("EAX: %x | EBX: %x | ECX: %x | ESI: %x\n",
      frame->eax, frame->ebx, frame->ecx,
      frame->esi);
}

void initialize_syscalls(void){
  register_IRQ(0x45, &handle_syscall);
}