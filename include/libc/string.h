#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Converts integer of base b to a string.
char* atoi(uint32_t n, int b);
void memcpy(void *dest, void *src, size_t n);
size_t strlen(char* n);

// Checks if two strings are equal. Returns 0 if true.
int strcmp(const char* a, const char* b);

// You should use containsChar before using stoi/stof
long int stoi(char* fmt);
float stof(char* s);

// Does s contain n? True if yes, false if no
bool containsChar(char* s, char n);
