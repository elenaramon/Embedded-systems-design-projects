#include "multiplier_testbench.h"
#include "multiplier_toplevel.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> clk;
    sc_signal<bool> rst;        
    sc_signal<bool> ready;

    sc_signal<sc_uint<32>> op1;
    sc_signal<sc_uint<32>> op2;
    
    sc_signal<bool> done;
    sc_signal<sc_uint<32>> result;
    sc_signal<sc_uint<3>> eccezione_res;

    multiplier_testbench    tb("tb");
    multiplier_toplevel     tl("tl");

    tb.clk(clk);
    tb.rst(rst);
    tb.ready(ready);
    tb.op1_out(op1);
    tb.op2_out(op2);
    tb.done(done);
    tb.result(result);
    tb.eccezione_in(eccezione_res);

    tl.clk(clk);
    tl.rst(rst);
    tl.ready(ready);
    tl.op1_in(op1);
    tl.op2_in(op2);
    tl.done(done);
    tl.result(result);
    tl.eccezione_out(eccezione_res);

    sc_start();

    return 0;
}