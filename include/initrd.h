#pragma once

#include <stdint.h>
#include <stddef.h>

#include "video/stdio.h"

#define FILE_ENDING 0xf9b6
#define SEPERATOR 0x9a
typedef struct {
  char name[64];           // File name
  unsigned char sep;       // Genuienly will help me a ton
  unsigned char buf[300];  // File contents
  unsigned short ending;
  int size;
} file_t;


#define INITRD_MAGIC 0x99
typedef struct {
  unsigned char magic;
  file_t files[256];   // Every single file available on the initrd
} initrd_t;
extern uint8_t initrd_buffer[270];
extern initrd_t initrd;

// Loads the initrd into initrd_buffer.
int load_initrd(uint32_t starting_area);
void generate_initrd(); // Generates a functioning initrd from the buffer.