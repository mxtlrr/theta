#include "coff.h"
#include "libc/string.h"

Coff_Ehdr* parse_coff(file_t file){
  if(file.buf[0] != COFF_MAGIC_BYTE0 && file.buf[1] == COFF_MAGIC_BYTE1)
    return NULL; // Invalid header, don't continue.
  Coff_Ehdr* header = (Coff_Ehdr*)file.buf;
  return header;
}

int execute_coff(Coff_Ehdr* header, file_t file){
  printf("Executing at %x...", header->entry);
  // Copy buffer to entry location
  memcpy(header->entry, file.buf, 300);
  int i = (*((int(* __attribute__((sysv_abi)))())(header->entry)))();
  return i;
}