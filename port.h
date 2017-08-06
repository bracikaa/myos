#ifndef __PORT_H
#define __PORT_H

#include "sizes.h"

  class Port 
  {
  protected:
    uint16_t portnumber;
    Port(uint16_t portnumber);
    ~Port();
  };
  
  class Port8 : public Port 
  {
  public:
    Port8(uint16_t portnumber);
    ~Port8();
    virtual void Write(uint8_t data);
    virtual uint8_t Read();
  };
  
  class Port8Slow : public Port8 
  {
  public:
    Port8Slow(uint16_t portnumber);
    ~Port8Slow();
    virtual void Write(uint8_t data);
  };
  
  class Port16 : public Port 
  {
  public:
    Port16(uint16_t portnumber);
    ~Port16();
    virtual void Write(uint16_t data);
    virtual uint16_t Read();
  };
  
  class Port32 : public Port 
  {
  public:
    Port32(uint16_t portnumber);
    ~Port32();
    virtual void Write(uint32_t data);
    virtual uint32_t Read();
  };


#endif