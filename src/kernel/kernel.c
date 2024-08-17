#include "multiboot.h"

#include <stdint.h>
#include "video/stdio.h"

#include "cpu/idt.h"

// Defined in gdt.asm
extern void load_gdt();

void kmain(multiboot_info_t* mbd, unsigned int magic){
  init_fb((uint32_t*)mbd->framebuffer_addr, mbd->framebuffer_pitch);

  load_gdt();
  printf("Loaded GDT!\n");

  idt_init();
  printf("Enabled IDT!\n");
  
  for(;;) asm("hlt");
}
