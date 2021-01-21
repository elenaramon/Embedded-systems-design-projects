//-------------------------------------------------------------
// Title:	Driver Library for m6502-Splatters platform
// Author:	Stefano Centomo
// Date:	15/06/2018
//-------------------------------------------------------------
#include "mmio.h"
#include "stdbool.h"
// Send op1 and op2 to multiplier connected to psel2, and return the result.
uint32_t mul(uint16_t op1, uint16_t op2);
// WRITE to IO module
void io_write(uint32_t data);
// READ from IO module
uint32_t io_read(void);
// Send VHDL_in_1, verilog_in_1, VHDL_in_2, verilog_in_2, VHDL_result and verilog_result to the floating point multiplier connected to psel3.
void floating_point_multiplication(uint32_t VHDL_in_1, uint32_t verilog_in_1, uint32_t VHDL_in_2, uint32_t verilog_in_2, uint32_t *VHDL_result, uint32_t *verilog_result);