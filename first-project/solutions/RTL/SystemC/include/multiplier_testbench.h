#include "systemc.h"

#define PERIOD 8
#define MANTISSA 23
#define ESPONENTE 8

SC_MODULE(multiplier_testbench) {

    sc_in<bool> done;
    sc_in<sc_uint<32>> result;
    sc_in<sc_uint<3>> eccezione_in;

    sc_out<bool> clk;
    sc_out<bool> rst;
    sc_out<bool> ready;

    sc_out<sc_uint<32>> op1_out;
    sc_out<sc_uint<32>> op2_out;

    sc_signal<bool> match_segno, match_mantissa, match_esponente, match_eccezione;

    sc_signal<bool> segno_in_1;
    sc_signal<sc_uint<ESPONENTE>> esponente_in_1;
    sc_signal<sc_uint<MANTISSA>> mantissa_in_1;
    sc_signal<sc_uint<3>> eccezione_in_1;

    sc_signal<bool> segno_in_2;
    sc_signal<sc_uint<ESPONENTE>> esponente_in_2;
    sc_signal<sc_uint<MANTISSA>> mantissa_in_2;
    sc_signal<sc_uint<3>> eccezione_in_2;

    void run();
    void clk_gen();

    SC_CTOR(multiplier_testbench) {

        SC_THREAD(run);
        sensitive << clk.pos();

        SC_THREAD(clk_gen);
    }
};