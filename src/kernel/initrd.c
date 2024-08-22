#include "initrd.h"

uint8_t initrd_buffer[270];

int load_initrd(uint32_t starting_area){
  for(int i = 0; i < 270; i++){
    initrd_buffer[i] = *(uint8_t*)(starting_area+i);
  }

  // Check for magic number
  if(initrd_buffer[0] == 0 && initrd_buffer[1] == INITRD_MAGIC) return 0;
  return 1;  // Something failed.
}