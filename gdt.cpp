#include "gdt.h"

GDT::GDT()
: nullDescriptor(0, 0, 0),
unusedDescriptor(0, 0, 0),
//starts at 0, has 64 mib
codeDescriptor(0, 64 * 1024 * 1024, 0x9A),
//starts at 0, has 64 mib
dataDescriptor(0, 64 * 1024 * 1024, 0x92)
{
  
  uint32_t i[2];
  i[0] = (uint32_t)this;
  i[1] = sizeof(GDT)<< 16;
  
  asm volatile("lgdt (%0)" : :"p" (((uint8_t *) i)+2));
}

GDT::~GDT()
{
  
}

uint16_t GDT::DataSegmentDescriptor()
{
  return (uint8_t*)&dataDescriptor - (uint8_t*)this;
}

uint16_t GDT::CodeSegmentDescriptor()
{
  return (uint8_t*)&codeDescriptor - (uint8_t*)this;
}

GDT::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t access)
{
  uint8_t* segment = (uint8_t*)this;
  
  if(limit <= 65536)
  {
    segment[6] = 0x40;
  }
  else 
  {
    if((limit & 0xFFF) != 0xFFF){
      limit = (limit >> 12) - 1;
    }
    else
      limit = limit >> 12;
    
    segment[6] = 0xC0;
  }
  segment[0] = limit & 0xFF;
  segment[1] = (limit >> 8) & 0xFF;
  segment[6] |= (limit >> 16) & 0xF;
  
  segment[2] = base & 0xFF;
  segment[3] = (base >> 8) & 0xFF;
  segment[4] = (base >> 16) & 0xFF;
  segment[7] = (base >> 24) & 0xFF;
  
  segment[5] = flags_limit_high;
}
  
  uint32_t GDT::SegmentDescriptor::Base()
  {
    uint8_t* segment = (uint8_t*)this;
    uint32_t result = segment[7];
    result = (result << 8) + segment[4];
    result = (result << 8) + segment[3];
    result = (result << 8) + segment[2];
    return result;
  }
  
  uint32_t GDT::SegmentDescriptor::Limit()
  {
    uint8_t* segment = (uint8_t*)this;
    uint32_t result = segment[6] & 0xF;
    result = (result << 8) + segment[1];
    result = (result << 8) + segment[0];
    
    if((segment[6] & 0xC0) == 0xC0)
      result = (result << 12) | 0xFFF;
    
    return result;
  }
 