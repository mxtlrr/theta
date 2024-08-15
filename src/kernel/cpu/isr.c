#include "cpu/isr.h"

__attribute__((noreturn))
void exception_handler(void){
  setcolor(0xFF0000);
  printf("Exception occurred. Halting!\n");
  for(;;) asm("cli; hlt");
}