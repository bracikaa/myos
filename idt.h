#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H
#include "sizes.h"
#include "port.h"
#include "gdt.h"


  class Interrupt
  {
    
  protected:
    struct IDT
    {
      uint16_t handlerLow;
      uint16_t gdt_code;
      uint8_t reserved;
      uint8_t access;
      uint16_t handlerHigh;
    }__attribute__((packed));
    
    
    static IDT idt[256];
    static void setIDTEntry(
      uint8_t interruptNumber,
      uint16_t gdtCodeOffset,
      void(*handler)(),
      uint8_t descriptorPrivilegeLvl,
      uint8_t descriptorType
      
    );
    
  public:
    Interrupt(GDT* gdt);
    ~Interrupt();
    
    static uint32_t handleInterrupt(uint8_t interruptNum, uint32_t stackPointer);
    
    
    static void IgnoreInterruptRequest();    
    //timer interupt
    static void HandleInterruptRequest0x00();
    //keyboard interrupt
    static void HandleInterruptRequest0x01();
    
  };

#endif