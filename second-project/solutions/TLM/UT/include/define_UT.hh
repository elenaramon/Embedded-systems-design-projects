#ifndef __define_UT_h__
#define __define_UT_h__

#include <systemc.h>

struct iostruct {
  float op1;
  float op2;
  float result;
};

#define ADDRESS_TYPE int
#define DATA_TYPE iostruct

#endif
