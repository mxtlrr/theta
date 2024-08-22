#include "initrd.h"

uint8_t initrd_buffer[270];
initrd_t initrd = {
  .magic = 0x99
};

int load_initrd(uint32_t starting_area){
  for(int i = 0; i < 270; i++){
    initrd_buffer[i] = *(uint8_t*)(starting_area+i);
  }

  // Check for magic number
  if(initrd_buffer[0] == 0 && initrd_buffer[1] == INITRD_MAGIC) return 0;
  return 1;  // Something failed.
}

// TODO: get this working for more than one file lol
void generate_initrd(){
  file_t files[256];
  // Skip magic bytes, those are already generated
  int ended_spot = 0;
  int spot_starting = 2;
  // File name
  for(int j = spot_starting; j < spot_starting+64; j++){
    if(initrd_buffer[j] == SEPERATOR) {
      ended_spot = j;
      break;
    }
    files[0].name[j-2] = initrd_buffer[j];
  }
  files[0].name[63] = '\0';

  // Now, get the file buffer
  int buf_spot = 0; int buf_ended = 0;
  for(int k = ended_spot+1; k < 270; k++){
    if(k == (FILE_ENDING>>8)) {
      buf_ended = buf_spot;
      spot_starting = buf_ended+3; // Magic number takes up 2 bytes. Skip to next byte.
      break;
    } // no more file contents
    files[0].buf[buf_spot] = initrd_buffer[k];
    buf_spot++;
  }
  files[0].buf[buf_ended+1] = '\0';
  initrd.files[0] = files[0];
}