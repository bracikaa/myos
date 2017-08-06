#include "idt.h"


void printf(char* str);

void Interrupt::setIDTEntry(
      uint8_t interruptNumber,
      uint16_t gdtCodeOffset,
      void(*handler)(),
      uint8_t descriptorPrivilegeLvl,
      uint8_t descriptorType) 
{
  
}

Interrupt::Interrupt(GDT* gdt)
{
}

Interrupt::~Interrupt()
{
}
    
    
uint32_t Interrupts::handleInterrupt(uint8_t interruptNum, uint32_t stackPointer)
{
  
  printf("LOADING INTERRUPTS!");
  return stackPointer;
}