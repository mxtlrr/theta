#pragma once

#include <stdint.h>

extern int x;
extern int y;

extern uint32_t color;


// Some from multiboot
extern uint32_t* vram;
extern uint32_t pitch;
void init_fb(uint32_t* v, uint32_t p);

void putpixel(uint32_t* vram, int x, int y, uint32_t color);

void setcolor(uint32_t newcol);

void putc(char c);
void puts(char* s);

void writestring(char* s);
