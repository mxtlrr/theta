#include "cpu/irq/kbd.h"
#include "cpu/irq/syscall.h"


void handle_syscall(registers_t* frame){
  // Max buffer size is 256. Change later (duh)
  char buffer[256] = { 0 };
  uint32_t byte_ct = 0;

  if(frame->eax < 2){
		if(frame->eax == 0){
			// ECX contains the count of bytes, and EBX points to the
    	// memory address where the buffer is located.
    	byte_ct = frame->ecx;

    	uint32_t address = 0xff00ba + (frame->ebx);
    	for(int i = 0; i != byte_ct; i++){
      	char character = (*(char*)(address+i));
      	buffer[i] = character;
    	}
		}
  }


  char ecx_buffer[frame->ecx]; // Buffer size -- used for SYS_READ

  switch(frame->eax){
    case SYS_WRITE:
      if(frame->esi != 0) setcolor(frame->esi);
      else setcolor(0xffffff); // "Disabling" color.
      for(int i = 0; buffer[i] != 0; i++){
        if(buffer[i] == SYS_WRITE_NL) putc('\n');
        else putc(buffer[i]);
      }
      break;
    
  // TODO: support space. 
  case SYS_READ:;
    uint8_t counter = 0;
    printf("Reading %d bytes\n", frame->ecx);
    while (counter < frame->ecx) {
      while((inb(0x64) & 0x01) == 0);
      
      uint8_t chr = inb(0x60);

      if(chr == 28) break; // Stop if enter recieved.
      if(chr < 100 && scanset[chr] != 0){
        ecx_buffer[counter] = scanset[chr];
        putc(scanset[chr]);
        counter++;
      }

    }
    ecx_buffer[counter] = '\0';

    // Then copy the buffer to the location in memory where ebx points to
    uint32_t address = 0xff00ba + (frame->ebx);
    memcpy((char*)address, ecx_buffer, frame->ecx);

    // Clear input buffer -- this may break in some places.
    while((inb(0x64) & 0x01) == 0);
    break;

		case FB_PLOTPIXEL:;
			// Color is already handled by the FB_SETCOLOR syscall.
			// All we need to do is plot at (EBX,ECX).
			uint32_t x_pos = frame->ebx;
			uint32_t y_pos = frame->ecx;

			putpixel(x_pos, y_pos, color);
			break;

		case FB_SETCOLOR:
			// ESI <- color
			setcolor(frame->esi);
			break;
  }
  return;
}

void initialize_syscalls(void){
  register_IRQ(IRQ_FROM_N(5), &handle_syscall);
}
