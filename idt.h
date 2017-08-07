#ifndef __INTERRUPT_H
#define __INTERRUPT_H
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
    
    struct idtPointer
    {
      uint16_t size;
      uint32_t base;
    }__attribute__((packed));
    
    static void setIDTEntry(
      uint8_t interruptNumber,
      uint16_t gdtCodeOffset,
      void(*handler)(),
      uint8_t descriptorPrivilegeLvl,
      uint8_t descriptorType
      
    );
    
    Port8Slow picMasterCommand;
    Port8Slow picSlaveCommand;
    Port8Slow picMasterData;
    Port8Slow picSlaveData;
    
  public:
    Interrupt(GDT* gdt);
    ~Interrupt();
    
    static uint32_t HandleInterrupt(uint8_t interruptNum, uint32_t stackPointer);
    
    void Activate();
    
    static void IgnoreInterruptRequest();    
    //timer interupt
    static void HandleInterruptRequest0x00();
    //keyboard interrupt
    static void HandleInterruptRequest0x01();
    
  };

#endif