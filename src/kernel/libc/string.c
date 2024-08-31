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
	for(d = 0; *n != 0; n++) d++;
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

long int stoi(char* fmt){
  long int res = 0;

  // 0x30 is used to convert to integer (0x34 '4' -> 0x04 [literal 4])
  for(int l = 0; l < strlen(fmt); l++) res = res*10 + (fmt[l]-0x30);
  return res;
}

float stof(char* s){
	float res = 0;
	int m = 0; int sign = 1;

	if(s[0] == '-'){
		sign = -1;
		m = 1;
	}

	for(; s[m] != '.' && s[m] != '\0'; m++) res = res*10 + (s[m]-0x30);
	if(s[m] == '.') m++; // Skip decimal. Next character is fractional bit

	float divisor = 1.0f;
	for(; s[m] != '\0'; m++){
		divisor *= 10;
		res += (s[m] - '0')/divisor;
	}
	return res*sign;
}

bool containsChar(char* s, char n){
	for(int i = 0; i < strlen(s); i++)
			if(s[i] == n) return true;
	return false;
}
