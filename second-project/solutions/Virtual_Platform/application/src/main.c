#include <stdbool.h>
#include "custom_stdlib.h"
#include "routines.h"


int main()
{
	uint32_t VHDL_in_1		= 2910978050;
	uint32_t verilog_in_1	= 2910978050;

	uint32_t VHDL_in_2		= 3212967938;
	uint32_t verilog_in_2	= io_read();
	
	uint32_t VHDL_result	= 0;
	uint32_t verilog_result	= 0;

	floating_point_multiplication(VHDL_in_1, verilog_in_1, VHDL_in_2, verilog_in_2, &VHDL_result, &verilog_result);
 	
	io_write(VHDL_result);
	io_write(verilog_result);

	return 0;
}
