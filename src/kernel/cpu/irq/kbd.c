#include "cpu/irq/kbd.h"

#define PROMPT "theta>"

char scanset[] = {
  0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', // 0-10
  '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 0, 0, // 11-27
  0, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 0, 0, 0, 'z', // 28-44
  'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 45-64
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 65-88
  0, 0
};

char scanset_capital[] = {
  0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', // 0-10
  ')', '_', '+', 0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0, 0, // 11-27
  0, 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', 0, 0, 0, 'Z', // 28-44
  'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 45-64
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 65-88
  0, 0
};

bool capslock = false;
bool lshift_on = false;

char buffer[256];
uint8_t buffer_count = 0;

void kbd_callback(registers_t* r){
	uint8_t chr = inb(0x60);
  // Is capslock?
  switch(chr){
    case CAPSLOCK_SC:
      capslock = !capslock;
      break;
    case SPACE: // Space
      putc(' ');
      buffer[buffer_count] = ' ';
      buffer_count++;
      break;
    case LSHIFT_PRESSED:
      lshift_on = true;
      break;
    case LSHIFT_RELEASED: // LShift off
      lshift_on = false;
      break;
    case ENTER:
      if(buffer[0] == 0) {
        printf("\n%s ", PROMPT);
        break;
      }
      buffer_count = 0;
      printf("\nChecking if buffer matches a file...");
      int exec = 0;
      for(int i = 0; i < 2; i++){
        if(strcmp(initrd.files[i].name, buffer) == 0){
          printf("it does! executing file \"%s\"\n", buffer);
          exec_binary(initrd.files[i]);
          exec = 1;
        }
      }
      if(exec == 0) printf("no match!\n");
      // TODO: handle like some math expression.

      printf("%s ", PROMPT);

      // Clear buffer
      for(int i = 0; i < 256; i++) buffer[i] = 0;
      break;
    default:
      if(chr < 100 && scanset[chr] != 0) {
        if(!capslock && !lshift_on) {
          putc(scanset[chr]);
          buffer[buffer_count] = scanset[chr];
        }
        if(capslock || lshift_on) {
          putc(scanset_capital[chr]);
            buffer[buffer_count] = scanset_capital[chr];
        }
        buffer_count++;
      } //else printf("-%d ", chr);
      break;
  }
}
void init_kbd(){
  // If there's any IRQ1/PS2 keyboard input, this will prevent us
  // from retrieving any more -- so let's just get the input.
  inb(0x60);
  register_IRQ(33, &kbd_callback);
  printf("%s ", PROMPT);
}