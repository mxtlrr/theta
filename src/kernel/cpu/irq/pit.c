#include "cpu/irq/pit.h"

volatile uint32_t ticks = 0;
uint32_t seconds = 0;

uint32_t get_ticks(void){
  return ticks;
}

void sleep(uint32_t time){
  uint32_t seconds_new = time+seconds;
  while(seconds != seconds_new){
    // Processor, we need you to sleep...
    asm("sti//hlt//cli");
  }
}


void callback(registers_t r){
  ticks++;
  if(ticks % 18 == 0) seconds++;
}

void init_pit(){
  register_IRQ(32, &callback);
}