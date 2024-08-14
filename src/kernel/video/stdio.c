#include "video/stdio.h"
#include "video/font.h"

int x = 0;
int y = 0;
uint32_t color = 0xffffff;

uint32_t* vram;
uint32_t pitch;


void setcolor(uint32_t newcol){
  color = newcol;
}

void putpixel(uint32_t* vram, int x, int y, uint32_t color){
  vram[1024*y+x] = color;
}

void putc(char c){
  char f[2] = { c, '\0' };
  writestring(f);
}

void puts(char* s){
  writestring(s);
}



void init_fb(uint32_t* v, uint32_t p){
  vram = v; pitch = p;
}

void writestring(char* s){
  unsigned char *ptr, *chr, *frg;
  unsigned int c;
  unsigned long long int o, p;
  int i, j, k, l, m, n;
  while(*s) {
    if((*s & 128) != 0) {
      if(!(*s & 32)) { c = ((*s & 0x1F)<<6)|(*(s+1) & 0x3F); s += 1; } else
      if(!(*s & 16)) { c = ((*s & 0xF)<<12)|((*(s+1) & 0x3F)<<6)|(*(s+2) & 0x3F); s += 2; } else
      if(!(*s & 8)) { c = ((*s & 0x7)<<18)|((*(s+1) & 0x3F)<<12)|((*(s+2) & 0x3F)<<6)|(*(s+3) & 0x3F); s += 3; }
      else c = 0;
    } else c = *s;
    s++;


    // TODO: implement scrolling
    // This one's kinda shitty.
    if(c == '\n'){
      int tmp = y + font->height;
      if(y != 1024 || tmp < 1024){
        x = 0;
        y += font->height;
      } else {
        y = 0;
      }
      continue;
    } else if(c == '\t'){
      x += chr[4]+1;
      x += chr[4]+1;
      x += chr[4]+1;
      x += chr[4]+1;
      continue;
    }

    if(x+10 >= 1010){
      x = 0;
      y += font->height;
      continue;
    }

    if(y > 760){
      y = 0;
      continue;
    }

    for(ptr = (unsigned char*)font + font->characters_offs, chr = 0, i = 0; i < 0x110000; i++) {
      if(ptr[0] == 0xFF) { i += 65535; ptr++; }
      else if((ptr[0] & 0xC0) == 0xC0) { j = (((ptr[0] & 0x3F) << 8) | ptr[1]); i += j; ptr += 2; }
      else if((ptr[0] & 0xC0) == 0x80) { j = (ptr[0] & 0x3F); i += j; ptr++; }
      else { if((unsigned int)i == c) { chr = ptr; break; } ptr += 6 + ptr[1] * (ptr[0] & 0x40 ? 6 : 5); }
    }
    if(!chr) continue;
    ptr = chr + 6; o = (unsigned long long int)vram + y * pitch + x * 4;
    for(i = n = 0; i < chr[1]; i++, ptr += chr[0] & 0x40 ? 6 : 5) {
      if(ptr[0] == 255 && ptr[1] == 255) continue;
      frg = (unsigned char*)font + (chr[0] & 0x40 ? ((ptr[5] << 24) | (ptr[4] << 16) | (ptr[3] << 8) | ptr[2]) :
        ((ptr[4] << 16) | (ptr[3] << 8) | ptr[2]));
      if((frg[0] & 0xE0) != 0x80) continue;
      o += (int)(ptr[1] - n) * pitch; n = ptr[1];
      k = ((frg[0] & 0x1F) + 1) << 3; j = frg[1] + 1; frg += 2;
      for(m = 1; j; j--, n++, o += pitch)
        for(p = o, l = 0; l < k; l++, p += 4, m <<= 1) {
          if(m > 0x80) { frg++; m = 1; }
          if(*frg & m) *((unsigned int*)p) = color;
        }
    }
    x += chr[4]+1; y += chr[5];
  }
}