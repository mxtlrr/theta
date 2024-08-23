#include "cpu/irq/syscall.h"

void handle_syscall(registers_t* frame){
  printf("RECIEVED SYSCALL!\n");
  
  // Fix frame by getting the lower bytes, i.e. get 0xDEAD from 0xFFDEAD.
  // Kinda yucky but it works for what it's worth.
  syscall_data_t syscall_data = {
    .eax = ((frame->eax >> 8) & 0xff) << 8 | (frame->eax & 0xff),
    .ebx = ((frame->ebx >> 8) & 0xff) << 8 | (frame->ebx & 0xff),
    .ecx = ((frame->ecx >> 8) & 0xff) << 8 | (frame->ecx & 0xff),
    .edx = ((frame->edx >> 8) & 0xff) << 8 | (frame->edx & 0xff),
    .esi = ((frame->esi >> 8) & 0xff) << 8 | (frame->esi & 0xff)
  };

  printf("Regs:\n   EAX: %x\n   EBX: %x\n   ECX: %x\n   EDX: %x\n   ESI: %x\n",
      syscall_data.eax, syscall_data.ebx, syscall_data.ecx,
      syscall_data.edx, syscall_data.esi);
}

void initialize_syscalls(void){
  register_IRQ(IRQ_FROM_N(5), &handle_syscall);
}