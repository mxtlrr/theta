#pragma once

#include "cpu/idt.h"
#include "cpu/isr.h"

#define PIT_CHANNEL0 0x40
#define PIT_CHANNEL1 0x41
#define PIT_CHANNEL2 0x42
#define MODE_CMD_REG 0x43 // Write only, read ignored.

// Channel0's count is 65535 typically, which makes
// the output ~18.20 Hz, aka an IRQ every (1000/18.20) ms,
// aka 54.94 ms.
#define TICK_SPEED 18

uint32_t get_ticks(void);
void init_pit();

// Sleep N seconds
void sleep(uint32_t time);