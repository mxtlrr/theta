#include "cpu/irq/kbd.h"

char scanset[] = {
  0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', // 0-10
  '0', 0, 0, 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 0, 0, // 11-27
  0, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 0, 0, 0, 'z', // 28-44
  'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 45-64
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 65-88
  0, 0
};

char scanset_capital[] = {
  0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', // 0-10
  ')', 0, 0, 0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0, 0, // 11-27
  0, 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', 0, 0, 0, 'Z', // 28-44
  'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 45-64
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 65-88
  0, 0
};

bool capslock = false;
bool lshift_on = false;

void kbd_callback(registers_t* r){
	uint8_t chr = inb(0x60);
  // Is capslock?
  switch(chr){
    case CAPSLOCK_SC:
      capslock = !capslock;
      break;
    case SPACE: // Space
      putc(' ');
      break;
    case LSHIFT_PRESSED:
      lshift_on = true;
      break;
    case LSHIFT_RELEASED: // LShift off
      lshift_on = false;
      break;
    case ENTER:
      putc('\n');
      break;
    default:
      if(chr < 100 && scanset[chr] != 0) {
        if(!capslock && !lshift_on) putc(scanset[chr]);
        if(capslock || lshift_on) putc(scanset_capital[chr]);
      }
      break;
  }
}
void init_kbd(){
  // If there's any IRQ1/PS2 keyboard input, this will prevent us
  // from retrieving any more -- so let's just get the input.
  inb(0x60);
  register_IRQ(33, &kbd_callback);
}