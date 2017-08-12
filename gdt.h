#ifndef __GDT_H
#define __GDT_H

#include "sizes.h"
    
    class GDT
    {
        public:
	  
	  //packed because it prevents the compiler from optimizing memory segments
            class Segment
            {
                private:
                    uint16_t limit_lo;
                    uint16_t base_lo;
                    uint8_t base_hi;
                    uint8_t type;
                    uint8_t limit_hi;
                    uint8_t base_vhi;

                public:
                    Segment(uint32_t base, uint32_t limit, uint8_t type);
                    uint32_t Base();
                    uint32_t Limit();
            } __attribute__((packed));

        private:
            Segment nullSegmentSelector;
            Segment unusedSegmentSelector;
            Segment codeSegmentSelector;
            Segment dataSegmentSelector;

        public:

            GDT();
            ~GDT();

            uint16_t CodeSegmentSelector();
            uint16_t DataSegmentSelector();
    };

#endif