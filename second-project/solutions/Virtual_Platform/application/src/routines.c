#include "routines.h"



//Multiplication Routine
uint32_t mul(uint16_t op1, uint16_t op2)
{
	// Prepare the variable used to read from pready.

	uint32_t result = 0x0000;

	// reset FLAGS
	reset_flags();
	// Prepare the data to send.
	set_pwdata_16(op1, op2);
	// Select the peripheral.
	set_psel(PSEL1);
	// Enable the operation.
	set_penable(1);
	// stay here untile prdata_rdy is ready.
	while (get_pready() == 0) __asm__("nop");
	// Get the result.
	result = get_prdata();
	// Disable the operation.
	set_penable(0);
	// Disable data stream from the bus.
	set_psel(NO_PSEL);
	//Clear Data
	//set_pwdata(0);
	// Return the result.
	return result;
}
void io_write(uint32_t data){

	reset_flags();
	// Set data to write on IO Module
	set_pwdata(data);
	// Set Write operation
	set_pwrite(1);
	//Select Peripheral 2
	set_psel(PSEL2);

	set_psel(NO_PSEL);
	set_penable(0);
	set_pwdata(0x00000000);
	set_pwrite(0);
	

}

uint32_t io_read(void){
	uint32_t data;
	reset_flags();
	// Set Read Operation
	set_pwrite(0);
	// Select Peripheral 2 = IO Module!
	set_psel(PSEL2);

	// stay here untile prdata_rdy is ready.
	while (get_pready() == 0) __asm__("nop");

	data = get_prdata();
	set_psel(NO_PSEL);
	set_penable(0);
	set_pwdata(0x00000000);
	set_pwrite(0);
	
	return data;
}

//Floating point multiplication Routine
void floating_point_multiplication(uint32_t VHDL_in_1, uint32_t verilog_in_1, uint32_t VHDL_in_2, uint32_t verilog_in_2, uint32_t *VHDL_result, uint32_t *verilog_result) {
	reset_flags();

	set_pwdata(VHDL_in_1);
	set_psel(PSEL3);
	set_penable(1);

	set_penable(0);

	set_pwdata(verilog_in_1);
	set_psel(PSEL3);
	set_penable(1);

	set_penable(0);

	set_pwdata(VHDL_in_2);
	set_psel(PSEL3);
	set_penable(1);

	set_penable(0);

	set_pwdata(verilog_in_2);
	set_psel(PSEL3);
	set_penable(1);

	set_penable(0);

	while (get_pready() == 0) __asm__("nop");

	*VHDL_result = get_prdata();

	set_penable(1);

	*verilog_result = get_prdata();

	set_penable(0);
	set_psel(NO_PSEL);
}
