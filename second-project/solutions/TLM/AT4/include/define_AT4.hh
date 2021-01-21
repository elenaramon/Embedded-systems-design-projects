#ifndef __define_AT4_h__
#define __define_AT4_h__

#include <systemc.h>

struct iostruct {
  float op1;
  float op2;
  float result;
};

#define ADDRESS_TYPE int
#define DATA_TYPE iostruct

#endif
