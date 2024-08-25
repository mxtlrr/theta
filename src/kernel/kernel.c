#include "multiboot.h"
#include "video/stdio.h"

#include "cpu/idt.h"

#include "cpu/irq/kbd.h"
#include "cpu/irq/pit.h"
#include "cpu/irq/syscall.h"

#include "info.h"
#include "mem/heap.h"
#include "exec.h"

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

  multiboot_module_t* m = (multiboot_module_t*)mbd->mods_addr;
  int result = load_initrd(m->mod_start);
  if(result != 0){
    printf("Failed to load inital ramdisk. Cannot continue.\n");
    for(;;);
  }
  printf("[ OK ] Loaded inital ramdisk\n");
	generate_initrd();
  initialize_syscalls();
	init_kbd();

	printf("\nWelcome to the Theta kernel. This is build %d.\nCompiled %s %s\nFiles on the ramdisk:\n", BUILD, __DATE__, __TIME__);

	setcolor(0x7b7b7b);
	for(int i = 0; i < 256; i++){
		if(initrd.files[i].name[0] == '\0') break;
		printf("   %s\n", initrd.files[i].name);
	}
	setcolor(0xffffff);
	printf("%s", PROMPT);
  for(;;) __asm__("hlt");
}
