#include "multiboot.h"

#include <stdint.h>
#include "video/stdio.h"

#include "cpu/idt.h"

#include "cpu/irq/kbd.h"
#include "cpu/irq/pit.h"

#include "mem/heap.h"

#include "libm/arith.h"
#include "libm/trig.h"

// Defined in gdt.asm
extern void load_gdt();


void kmain(multiboot_info_t* mbd, unsigned int magic){
  init_fb((uint32_t*)mbd->framebuffer_addr, mbd->framebuffer_pitch);
  if(!(mbd->flags >> 6 & 1)){
    printf("Invalid MMap. Cannot continue.\n");
    for(;;);
  }

  load_gdt();
  printf("Loaded GDT!\n");

  idt_init();
  printf("Enabled IDT!\n");

  init_pit();
  printf("\n");
  
	for(int i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)){
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
    // Add the block to the blocks
    if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE){
      block_t nb = {
        .free = true,
        .location = mmmt->addr_low,
        .size = mmmt->len_low
      };

      add_block(nb);
  	  printf("Start addr -> %x | Length: %x | Size: %x | Type: %d | Usable: %s\n",
			  	mmmt->addr_low, mmmt->len_low, mmmt->size, mmmt->type, mmmt->type-1 ? "No" : "Yes");
    }
  
	}

  // Testing malloc:)
  printf("\nTesting malloc...\n");
  setcolor(0x123456);
  uint32_t v = malloc(7);
  printf("Allocated 7 bytes to address %x...", v);

  // Free
  free(v);
  printf("%x is now freed.\n");

  init_kbd();
  for(;;) asm("hlt");
}
