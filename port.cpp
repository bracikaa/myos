#include "port.h"


Port::Port(uint16_t portnumber)
{
  this->portnumber = portnumber;
}
Port::~Port()
{
  
}

//8bit ports
Port8::Port8(uint16_t portnumber)
:Port(portnumber)
{
  
}
Port8::~Port8()
{
}
void Port8::Write(uint8_t data)
{
  __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portnumber));
}

uint8_t Port8::Read()
{
  uint8_t result;
  __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd"(portnumber));
  return result;
}

//8slow
Port8Slow::Port8Slow(uint16_t portnumber)
:Port8(portnumber)
{
  
}
Port8Slow::~Port8Slow()
{
}
void Port8Slow::Write(uint8_t data)
{
  __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1: " : : "a" (data), "Nd" (portnumber));
}


//16bit ports
Port16::Port16(uint16_t portnumber)
:Port(portnumber)
{
  
}
Port16::~Port16()
{
}
void Port16::Write(uint16_t data)
{
  __asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (portnumber));
}

uint16_t Port16::Read()
{
  uint16_t result;
  __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd"(portnumber));
  return result;
}

//32bit port
Port32::Port32(uint16_t portnumber)
:Port(portnumber)
{
  
}
Port32::~Port32()
{
}
void Port32::Write(uint32_t data)
{
  __asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (portnumber));
}

uint32_t Port32::Read()
{
  uint32_t result;
  __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd"(portnumber));
  return result;
}