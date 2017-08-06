#ifndef __GDT_H
#define __GDT_H
#include "sizes.h"

  class GDT
  {
  public:
    class SegmentDescriptor
    {
    private:
      uint16_t limit_low;
      uint16_t base_low;
      uint8_t base_middle;
      uint8_t access;
      uint8_t flags_limit_high;
      uint8_t base_high;
      
    public:
      SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t access);
      uint32_t Base();
      uint32_t Limit();
  
    }__attribute__((packed));
    
    SegmentDescriptor nullDescriptor;
    SegmentDescriptor unusedDescriptor;
    SegmentDescriptor codeDescriptor;
    SegmentDescriptor dataDescriptor;
    
  public:
    GDT();
    ~GDT();
    
    uint16_t CodeSegmentDescriptor();
    uint16_t DataSegmentDescriptor();
  };

#endif