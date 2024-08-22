#pragma once

#include <stdint.h>
#include <stddef.h>

// Converts integer of base b to a string.
char* atoi(uint32_t n, int b);
void memcpy(void *dest, void *src, size_t n);