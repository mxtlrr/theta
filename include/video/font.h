#pragma once

typedef struct {
  unsigned char  magic[4];
  unsigned int   size;
  unsigned char  type;
  unsigned char  features;
  unsigned char  width;
  unsigned char  height;
  unsigned char  baseline;
  unsigned char  underline;
  unsigned short fragments_offs;
  unsigned int   characters_offs;
  unsigned int   ligature_offs;
  unsigned int   kerning_offs;
  unsigned int   cmap_offs;
} __attribute__((packed)) ssfn_font_t;

extern unsigned char font_data[8283];
extern ssfn_font_t* font;