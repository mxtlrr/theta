#include "exec.h"

uint32_t mem_addr[3] = {
  0xff00ba, // These are just random addresses.
  0xcfd962,
  0xee8025
};


uint8_t modify_address = 0;
uint32_t get_valid_addr(file_t handle){
  for(int i = 0; i < 3; i++){
    uint32_t value = *(uint32_t*)mem_addr[i];
    if(value == 0) return mem_addr[i];
		else {
			// Get first three bytes of buffer and check if they
			// are equal.
			uint32_t byte1 = value & 0xff;
			uint32_t byte2 = (value >> 8) & 0xff;
			uint32_t byte3 = ((value >> 8) >> 8) & 0xff;

			if(byte1 == handle.buf[0] && byte2 == handle.buf[1] &&
					byte3 == handle.buf[2]){
				modify_address = 1;
				return mem_addr[i];
			}
		}
  } 
  // Still here?
  return 0;
}

extern void run_binary(uint32_t); // Exec_bin.asm, probably bad
                                  // to put it in a C file but oh well
void exec_binary(file_t file){
  // Get valid address
  uint32_t addr_to_cp = get_valid_addr(file);
  setcolor(0x00ff00);
  

	// Copy address in memory
  if(modify_address == 0)	memcpy((char*)(uintptr_t)addr_to_cp, file.buf, 300);
	// Don't copy if we're already 
	// Run binary program
  setcolor(0xffffff);
  run_binary(addr_to_cp);
}
