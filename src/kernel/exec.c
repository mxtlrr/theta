#include "exec.h"

uint32_t mem_addr[3] = {
  0xff00ba, // These are just random addresses.
  0xcfd962,
  0xee8025
};

uint32_t get_valid_addr(){
  for(int i = 0; i < 3; i++){
    uint32_t value = *(uint32_t*)mem_addr[i];
    if(value == 0) return mem_addr[i];
  } 
  // Still here?
  return 0;
}

extern void run_binary(uint32_t); // Exec_bin.asm, probably bad
                                  // to put it in a C file but oh well
void exec_binary(file_t file){
  // Get valid address
  uint32_t addr_to_cp = get_valid_addr();
  printf("Loading binary \"%s\" to address %x...", file.name,
      addr_to_cp);

  // Copy address in memory
  memcpy((char*)(uintptr_t)addr_to_cp, file.buf, 300);
  
  // Run binary program
  run_binary(addr_to_cp);
}