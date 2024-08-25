#include "cpu/irq/syscall.h"

syscall_data_t gen_table(registers_t* frame){
  syscall_data_t r = {
    .eax = ((frame->eax >> 8) & 0xff) << 8 | (frame->eax & 0xff),
    .ecx = ((frame->ecx >> 8) & 0xff) << 8 | (frame->ecx & 0xff),
    .edx = ((frame->edx >> 8) & 0xff) << 8 | (frame->edx & 0xff)
  };
  return r;
}

void handle_syscall(registers_t* frame){
  // Fix frame, get lower bytes for stuff we don't need to get ALL bytes
  // for.
  syscall_data_t syscall_data = gen_table(frame);

  // Max buffer size is 256. Change later (duh)
  char buffer[256] = { 0 };
  uint32_t byte_ct = 0;

  if(syscall_data.eax < 2){
    // For both SYS_READ and SYS_WRITE, EBX is used for the buffer
    syscall_data.ebx = ((frame->ebx >> 8) & 0xff) << 8 | (frame->ebx & 0xff);
		syscall_data.esi = frame->esi;

		if(syscall_data.eax == 0){
			// ECX contains the count of bytes, and EBX points to the
    	// memory address where the buffer is located.
    	byte_ct = syscall_data.ecx;

    	uint32_t address = 0xff00ba + (frame->ebx);
    	for(int i = 0; i != byte_ct; i++){
      	char character = (*(char*)(address+i));
      	buffer[i] = character;
    	}
		}

  } else {
    if(syscall_data.eax == FB_SETCOLOR){
      // ESI is used as the color.
      syscall_data.esi = frame->esi;
    } else syscall_data.esi = ((frame->esi >> 8) & 0xff) << 8 | (frame->esi & 0xff);

    syscall_data.ebx = frame->ebx;
  }


  switch(syscall_data.eax){
    case SYS_WRITE:
      if(syscall_data.esi != 0) setcolor(syscall_data.esi);
      else setcolor(0xffffff); // "Disabling" color.
      for(int i = 0; buffer[i] != 0; i++){
        if(buffer[i] == SYS_WRITE_NL) putc('\n');
        else putc(buffer[i]);
      }
      break;

		case FB_PLOTPIXEL:;
			// Color is already handled by the FB_SETCOLOR syscall.
			// All we need to do is plot at (EBX,ECX).
			uint32_t x_pos = syscall_data.ebx;
			uint32_t y_pos = syscall_data.ecx;
			printf("Color is %x, plotting at (%d, %d)\n", color, x_pos, y_pos);

			putpixel(x_pos, y_pos, color);
			break;

		case FB_SETCOLOR:
			// ESI <- color
			printf("Setting color to %x\n", frame->esi);
			setcolor(frame->esi);
			break;
  }
  return;
}

void initialize_syscalls(void){
  register_IRQ(IRQ_FROM_N(5), &handle_syscall);
}
