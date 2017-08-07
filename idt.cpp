#include "idt.h"


void printf(char* str);

Interrupt::IDT Interrupt::idt[256];


void Interrupt::setIDTEntry(
      uint8_t interruptNumber,
      uint16_t gdtCodeOffset,
      void(*handler)(),
      uint8_t descriptorPrivilegeLvl,
      uint8_t descriptorType) 
{
      const uint8_t IDT_DESC_PRESENT = 0x00;
      //how entries are set
      idt[interruptNumber].handlerLow = ((uint32_t) handler) & 0xFFFF;
      idt[interruptNumber].handlerHigh = (((uint32_t) handler) >> 16) & 0xFFFf;
      idt[interruptNumber].gdt_code = gdtCodeOffset;
      idt[interruptNumber].access = IDT_DESC_PRESENT | descriptorType | ((descriptorPrivilegeLvl & 3) << 5);
      idt[interruptNumber].reserved = 0;
}

Interrupt::Interrupt(GDT* gdt)
: picMasterCommand(0x20),
  picMasterData(0x21),
  picSlaveCommand(0xA0),
  picSlaveData(0xA1)
  {
 //constructor sets the entries
 //caling the codesegmentselector from gdt
  uint16_t codeSegment = gdt->CodeSegmentDescriptor();
  const uint8_t IDT_INTERRUPT_GATE = 0xE;
  
  for(uint16_t i = 0; i < 256; i++)
  {
    //setting entries, privilege level 0 - kernelspace, or ignore request
    setIDTEntry(i, codeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
  }
  //handler request for the assembly handlers
  setIDTEntry(0x20, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
  setIDTEntry(0x21, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
  
  //before the cpu uses the idt, we need to communicate with teh picSlaveCommand
  picMasterCommand.Write(0x11);
  picSlaveCommand.Write(0x11);
  //master pic if gets any interrupt get 0x20 to it, slave 0x28, those pics have 8 interrupts
  picMasterData.Write(0x20);
  picSlaveData.Write(0x28);
  
  picMasterData.Write(0x04);
  picSlaveData.Write(0x02);
  
  picMasterData.Write(0x01);
  picSlaveData.Write(0x01);

  picMasterData.Write(0x00);
  picSlaveData.Write(0x00);  
  
  idtPointer idtp;
  
  //256 interrupt entries
  idtp.size = 256 * sizeof(IDT) - 1;
  idtp.base = (uint32_t) idt;
  //load idt
  //creating teh table, telling cp to use the table, still need to start sending interrupts to the pic
  asm volatile("lidt %0" : : "m" (idtp));
  
  
}

Interrupt::~Interrupt()
{
}

void Interrupt::Activate()
{
  asm("sti");
}
    
    
uint32_t Interrupt::HandleInterrupt(uint8_t interruptNum, uint32_t stackPointer)
{
  
  printf("LOADING INTERRUPTS!");
  return stackPointer;
}