#include <stdbool.h>

#include "libc/string.h"

char* atoi(uint32_t n, int b){
  static char hex[] = "0123456789ABCDEF";
  static char buf[50];
  char* ptr;
  // Make sure we have a valid string -- last
  // input in buf needs to be a nullptr
  ptr = &buf[49]; *ptr='\0';

  if(n == 0) return "0";


  // Handle negative numbers, extremely important :^)
  bool z = (n>=2147483648);
  if (z && b == 10) n = -((int32_t)n);

  // Convert the number to the string
  for (; n != 0; n /= b) *--ptr = hex[n % b];

  // Add negative sign for base 10, after its converted
  if (z && b == 10) *--ptr = '-';
  return ptr;
}

void memcpy(void *dest, void *src, size_t n) { 
  char *csrc = (char *)src; 
  char *cdest = (char *)dest; 

  for (int i=0; i<n; i++) cdest[i] = csrc[i]; 
}

size_t strlen(char* n){
  int d;
	for(d = 0; *n != 0; *n++) d++;
	return d;
}


int strcmp(const char* a, const char* b){
  const unsigned char *s1 = (const unsigned char *)a;
  const unsigned char *s2 = (const unsigned char *)b;
  unsigned char c1, c2;
  do {
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
	  if (c1 == '\0') return c1 - c2;
  } while (c1 == c2);
  return c1 - c2;
}