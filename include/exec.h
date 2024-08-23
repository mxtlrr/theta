/* Running executable files lol */
#pragma once

#include <stdint.h>
#include <stddef.h>

#include "initrd.h"

// Memory addresses we load the flat binary to.
extern uint32_t mem_addr[3];

// Check each address in mem_addr. If it's 0, then we use that
uint32_t get_valid_addr();

// Execute the binary in file.buf
void exec_binary(file_t file);