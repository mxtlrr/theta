#include "multiboot.h"
#include "video/stdio.h"

#include "cpu/idt.h"

#include "cpu/irq/kbd.h"
#include "cpu/irq/pit.h"

#include "info.h"
#include "mem/heap.h"

// Defined in gdt.asm
extern void load_gdt();


void kmain(multiboot_info_t* mbd, unsigned int magic){
  init_fb((uint32_t*)mbd->framebuffer_addr, mbd->framebuffer_pitch);

  if(!(mbd->flags >> 6 & 1)){
    printf("Invalid MMap. Cannot continue.\n");
    for(;;);
  }

  load_gdt();
  printf("[ OK ] GDTR Setup!\n");

  idt_init();
  printf("[ OK ] IDTR Setup!\n");

  init_pit();
  
	for(int i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)){
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
    // Add the block to the blocks
    if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE){
      block_t nb = {
        .free = true, .location = mmmt->addr_low, .size = mmmt->len_low
      };

      add_block(nb);
    	printf("[ OK ] Added entry to memory map.\n");
		}  
	}
  init_kbd();

	printf("\nWelcome to the Theta kernel. This is build %d.\nCompiled %s %s\n", BUILD, __DATE__, __TIME__);
	printf("%s", PROMPT);

  for(;;) __asm__("hlt");
}
