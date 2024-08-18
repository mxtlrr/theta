#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "video/stdio.h"

#define IN_USE 0x00
#define FREE   0x01

#define MAX_BLOCKS 255


typedef struct {
  bool     free;
  uint32_t location;    // Where is the block in physical
                        // memory?
  uint32_t size;        // How big?
} block_t;

extern block_t blocks[MAX_BLOCKS];
extern uint8_t blockcounter;

// Adds block to the next location. Automatically
// increments blockcounter
void add_block(block_t block);

// Allocates n bytes and returns the value to the start
// of that.
uint32_t malloc(uint32_t n);

// Frees that memory allocated
void free(uint32_t mm_val);