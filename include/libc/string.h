#pragma once

#include <stdint.h>
#include <stddef.h>

// Converts integer of base b to a string.
char* atoi(uint32_t n, int b);
void memcpy(void *dest, void *src, size_t n);
size_t strlen(char* n);

// Checks if two strings are equal. Returns 0 if true.
int strcmp(const char* a, const char* b);

// Converts a string to an integer.
#define BAD_STRING -1
long int stoi(char* fmt);