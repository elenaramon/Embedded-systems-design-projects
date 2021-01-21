#include "systemc.h"
#include "multiplier.h"

SC_MODULE(multiplier_toplevel) {
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_in<bool> ready;

    sc_in<sc_uint<32>> op1_in;
    sc_in<sc_uint<32>> op2_in;

    sc_out<bool> done;
    sc_out<sc_uint<32>> result;
    sc_out<sc_uint<3>> eccezione_out;

    multiplier multiplier_1, multiplier_2;

    typedef enum {S0, S1, S2, S3, S4, S5, S6, S7, S8} STATE;

    sc_signal<STATE> current_state, next_state;

    sc_signal<sc_uint<32>> res1_out;
    sc_signal<sc_uint<32>> res2_out;

    sc_signal<bool> done_1;
    sc_signal<sc_uint<3>> eccezione_out_1;

    sc_signal<bool> done_2;
    sc_signal<sc_uint<3>> eccezione_out_2;

    void fsm(void);
    void datapath(void);

    SC_CTOR(multiplier_toplevel) : multiplier_1("multiplier_1"), multiplier_2("multiplier_2") {
        multiplier_1.clk(clk);
        multiplier_1.rst(rst);
        multiplier_1.ready(ready);
        multiplier_1.op(op1_in);
        multiplier_1.done(done_1);
        multiplier_1.result(res1_out);
        multiplier_1.eccezione_out(eccezione_out_1);

        multiplier_2.clk(clk);
        multiplier_2.rst(rst);
        multiplier_2.ready(ready);
        multiplier_2.op(op2_in);
        multiplier_2.done(done_2);
        multiplier_2.result(res2_out);
        multiplier_2.eccezione_out(eccezione_out_2);

        SC_METHOD(fsm);
        sensitive << current_state << ready << done_1 << done_2;

        SC_METHOD(datapath);
        sensitive << rst.neg();
        sensitive << clk.pos();
    }
};