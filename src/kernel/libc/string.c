#include "libc/string.h"

char* atoi(uint32_t n, int b){
  static char hex[] = "0123456789ABCDEF";
  static char buf[50];
  char* ptr;

  // Make sure we have a valid string -- last
  // input in buf needs to be a nullptr
  ptr = &buf[49]; *ptr='\0';

  // Actually convert it.
  for(; n != 0; n /= b) *--ptr = hex[n%b];
  return ptr;
}