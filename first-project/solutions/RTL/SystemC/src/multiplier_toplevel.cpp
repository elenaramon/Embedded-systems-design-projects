#include "systemc.h"
#include "multiplier_toplevel.h"

void multiplier_toplevel::fsm(void) {
    switch (current_state) {
        case S0:
            if (ready.read() == 0) {
                next_state = S0;
            }
            else {
                next_state = S1;
            }
            break;
        case S1:
            if (done_1.read() == 0 && done_2.read() == 0) {
                next_state = S1;
            }
            else if (done_1.read() == 1 && done_2.read() == 1) {
                next_state = S2;
            }
            else if (done_1.read() == 1 && done_2.read() == 0) {
                next_state = S3;
            }
            else {
                next_state = S4;
            }
            break;
        case S2:
            next_state = S5;
            break;
        case S3:
            if (done_2.read() == 0) {
                next_state = S6;
            }
            else {
                next_state = S5;
            }
            break;
        case S4:
            if (done_1.read() == 0) {
                next_state = S7;
            }
            else {
                next_state = S5;
            }
            break;
        case S5:
            next_state = S8;
            break;
        case S6:
            if (done_2.read() == 0) {
                next_state = S6;
            }
            else {
                next_state = S5;
            }
            break;
        case S7:
            if (done_1.read() == 0) {
                next_state = S7;
            }
            else {
                next_state = S5;
            }
            break;
        case S8:
            next_state = S0;
            break;
    }
}

void multiplier_toplevel::datapath(void) {
    if (rst.read() == 1) {
        current_state = S0;
    }
    else if (clk.read() == 1) {
        current_state = next_state;
        switch (next_state) {
            case S0:
                // segno_out.write(0);
                // esponente_out.write(0);
                // mantissa_out.write(0);
                result.write(0);
                eccezione_out.write(0);
                done.write(0);
                break;
            case S1:
                // empty
                break;
            case S2:
                // empty
                break;
            case S3:
                // empty
                break;
            case S4:
                // empty
                break;
            case S5:
                // segno_out.write(segno_out_1);
                // esponente_out.write(esponente_out_1);
                // mantissa_out.write(mantissa_out_1);
                result.write(res1_out);
                eccezione_out.write(eccezione_out_1);
                done.write(1);
                break;
            case S6:
                // empty
                break;
            case S7:
                // empty
                break;
            case S8:
                // segno_out.write(segno_out_2);
                // esponente_out.write(esponente_out_2);
                // mantissa_out.write(mantissa_out_2);
                result.write(res2_out);
                eccezione_out.write(eccezione_out_2);
                break;
        }
    }
}