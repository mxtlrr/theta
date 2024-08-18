/* Definently could use a rework. But this should be fine for now. */
#include "mem/heap.h"

block_t blocks[MAX_BLOCKS] = {0};
uint8_t blockcounter = 0;

int shittercounter = 0;

void add_block(block_t block){
  blocks[blockcounter] = block;
  blockcounter++;
}

uint32_t malloc(uint32_t n){
  // Are there any blocks that are >= n?
  int index = -1;
  for(int i = 0; i < 256; i++){
    if(blocks[i].size >= n){
      // Yes, get the first one that is FREE!
      if(blocks[i].free == true){
        index = i;
        break;
      }
    }
  }

  // I couldn't find anything... :/
  if(index == -1) return NULL;

  // If the size is greater, than we split it into two
  if(blocks[index].size > n){
    block_t new_block = {
      .free = false,
      .location = blocks[index].location,
      .size = n
    };

    block_t old_block = blocks[index];
    old_block.size = (old_block.size) - n;

    // Offset every other block by 1
    for(int i = index; i < MAX_BLOCKS; i++){
      if(i < 255) blocks[i+1] = blocks[i];
    }

    // Now, blocks[index] is free, set it to our
    // new block, which is the one we're mallocating.
    blocks[index]   = new_block;
    blocks[index+1] = old_block;
    return blocks[index].location;
  }

  // This one is the easiest one!
  if(blocks[index].size == n){
    block_t modified_block = {
      .free     = false,
      .location = blocks[index].location,
      .size     = n
    };
    blocks[index] = modified_block;

    return modified_block.location;
  }
}

void free(uint32_t mm_val){
  // Find the block that's location is mm_val,
  // it has to exist there somewhere
  int index = -1;
  for(int i = 0; i < 256; i++){
    if(blocks[i].location == mm_val){
      index = i;
      break;
    }
  }

  if(index == -1) for(;;) asm("cli//hlt"); // ???. Halt CPU cuz wtf happened LOL
  // Then we just set it as free
  blocks[index].free = true;
}