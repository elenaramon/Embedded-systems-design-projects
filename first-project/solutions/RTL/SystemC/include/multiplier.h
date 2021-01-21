#include "systemc.h"

#define MANTISSA 23
#define ESPONENTE 8
#define DOUBLE_MANTISSA 48

SC_MODULE(multiplier) {
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_in<bool> ready;
    sc_in<sc_uint<32>> op;

    sc_out<bool> done;
    sc_out<sc_uint<32>> result;
    sc_out<sc_uint<3>> eccezione_out;


    typedef enum {S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, S16, S17, S18, S19, S20, S21, S22, S23, S24, S25, S26, S27, S28, S29, S30, S31, S32, S33, S_Reset} STATE;

    sc_signal<sc_uint<MANTISSA + 1>> mantissa_op1, mantissa_op2;
    sc_signal<bool> segno_op1, segno_op2;
    sc_signal<sc_uint<ESPONENTE>> esponente_op1, esponente_op2;
    sc_signal<sc_uint<DOUBLE_MANTISSA>> temp_mantissa;
    sc_signal<sc_uint<MANTISSA + 2>> mantissa;
    sc_signal<sc_uint<ESPONENTE + 1>> t7, esponente;
    sc_signal<bool> t1, t2, t3, t4, t5, t6;
    sc_signal<STATE> current_state, next_state;
    sc_signal<sc_uint<3>> eccezione;
    sc_signal<sc_uint<DOUBLE_MANTISSA>> moltiplicando;
    sc_signal<int> counter;


    void fsm(void);
    void datapath(void);

    SC_CTOR(multiplier) {
        
        SC_METHOD(fsm);
        sensitive << ready << t1 << t2 << t3 << t4 << t5 << t6 << counter << mantissa_op2 << temp_mantissa << esponente << mantissa << current_state;

        SC_METHOD(datapath);
        sensitive << rst.neg();
        sensitive << clk.pos();
    }
    
};