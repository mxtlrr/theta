/* Coff parser or whatever */
#pragma once

/* Djgpp generates 0x14c */
#define COFF_MAGIC_BYTE0 0x4c
#define COFF_MAGIC_BYTE1 0x01

#include "initrd.h"

typedef struct {
  unsigned short 	magic;
	unsigned short 	vstamp;
	unsigned long 	tsize;
	unsigned long 	dsize;
	unsigned long 	bsize;
	unsigned  int 	text_start;     /* Base of Text used for this file */
	unsigned  int 	entry;          /* Entry point                     */
	unsigned long 	data_start;   
} Coff_Ehdr;

Coff_Ehdr* parse_coff(file_t file);

// Executes the _start of some COFF file's header "header".
int execute_coff(Coff_Ehdr* header, file_t file);