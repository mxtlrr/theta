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

void memcpy(void *dest, void *src, size_t n) { 
// Typecast src and dest addresses to (char *) 
char *csrc = (char *)src; 
char *cdest = (char *)dest; 

// Copy contents of src[] to dest[] 
for (int i=0; i<n; i++) 
    cdest[i] = csrc[i]; 
} 

// TODO: get this working for more than one file lol
initrd_t generate_initrd(){
  file_t files[256];
  // Skip magic bytes, those are already generated
  int ended_spot = 0;
  int spot_starting = 2;
  for(int i = 0; i < 2; i++){
    // File name
    for(int j = spot_starting; j < spot_starting+64; j++){
      if(initrd_buffer[j] == SEPERATOR) {
        ended_spot = j;
        break;
      }
      files[i].name[j-2] = initrd_buffer[j];
    }
    files[i].name[63] = '\0';

    // Now, get the file buffer
    int buf_spot = 0; int buf_ended = 0;
    for(int k = ended_spot+1; k < 270; k++){
      if(k == (FILE_ENDING>>8)) {
        buf_ended = buf_spot;
        spot_starting = buf_ended+3; // Magic number takes up 2 bytes. Skip to next byte.
        break;
      } // no more file contents
      files[i].buf[buf_spot] = initrd_buffer[k];
      buf_spot++;
    }
    files[i].buf[buf_ended+1] = '\0';
  }
  initrd_t generated = { .magic = INITRD_MAGIC };
  for(int i = 0; i < 2; i++){
    generated.files[i] = files[i];
  }
  return generated;
}