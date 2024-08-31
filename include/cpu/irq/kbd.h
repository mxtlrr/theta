#pragma once

#include "cpu/isr.h"
#include "cpu/idt.h"
#include "cmd-parse.h"

#define PROMPT "theta> "

#define PS2_COMMAND  0x64
#define PS2_DATAPORT 0x64
#define SCANCODE1 43

#define ACK 0xfa
#define RESEND 0xfe

#define CAPSLOCK_SC 58
#define SPACE 57
#define LSHIFT_PRESSED  42
#define LSHIFT_RELEASED 170

#define RSHIFT_PRESSED 54
#define RSHIFT_RELEASED 182
#define ENTER 28

void kbd_callback(registers_t* r);
void init_kbd();


extern char scanset[];
extern char scanset_capital[];
