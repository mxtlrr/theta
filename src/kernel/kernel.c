#include "multiboot.h"

#include <stdint.h>
#include "video/stdio.h"

void kmain(multiboot_info_t* mbd, unsigned int magic){
  init_fb((uint32_t*)mbd->framebuffer_addr, mbd->framebuffer_pitch);
  putc('Z');
}