#include "multiplier.h"

void multiplier::fsm(void) {
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
            next_state = S2;
            break;
        case S2:
            next_state = S3;
            break;
        case S3:
            if (t1.read() && t3.read()) {
                next_state = S4;
            }
            else if (t2.read() && t4.read()) {
                next_state = S5;
            }
            else if ((t1.read() && t4.read()) || (t2.read() && t3.read())) {
                next_state = S6;
            }
            else if ((t1.read() && !t3.read()) || (t3.read() && !t1.read())) {
                next_state = S7;
            }
            else if ((t2.read() && !t4.read()) || (!t2.read() && t4.read())) {
                next_state = S8;
            }
            else {
                next_state = S9;
            }
            break;
        case S4:
            if (t5.read() && t6.read()) {
                next_state = S19;
            }
            else {
                next_state = S10;
            }
            break;
        case S5:
            if (t5.read() && t6.read()) {
                next_state = S19;
            }
            else {
                next_state = S11;
            }
            break;
        case S6:
            if (t5.read() && t6.read()) {
                next_state = S12;
            }
            else if (!(t5.read() && t6.read())) {
                next_state = S13;
            }
            else if ((!t5.read() && t1.read()) || (!t6.read() && t3.read())) {
                next_state = S14;
            }
            else {
                next_state = S15;
            }
            break;
        case S7:
            if (t5.read() && t6.read()) {
                next_state = S19;
            }
            else {
                next_state = S16;
            }
            break;
        case S8:
            if (t5.read() && t6.read()) {
                next_state = S19;
            }
            else {
                next_state = S17;
            }
            break;
        case S9:
            next_state = S20;
            break;
        case S10:
            next_state = S18;
            break;
        case S11:
            next_state = S18;
            break;
        case S12:
            next_state = S18;
            break;
        case S13:
            next_state = S18;
            break;
        case S14:
            next_state = S18;
            break;
        case S15:
            next_state = S18;
            break;
        case S16:
            next_state = S18;
            break;
        case S17:
            next_state = S18;
            break;
        case S18:
            next_state = S0;
            break;
        case S19:
            next_state = S0;
            break;
        case S20:
            if (counter.read() < 24) {
                next_state = S21;
            }
            else {
                next_state = S24;
            }
            break;
        case S21:
            if (mantissa_op2.read()[counter] == 1) {
                next_state = S22;
            }
            else {
                next_state = S23;
            }
            break;
        case S22:
            next_state = S23;
            break;
        case S23:
            next_state = S20;
            break;
        case S24:
            if (temp_mantissa.read()[47] == 1) {
                next_state = S25;
            }
            else {
                next_state = S26;
            }
            break;
        case S25:
            next_state = S26;
            break;
        case S26:
            if (esponente.read()[8] == 1) {
                next_state = S27;
            }
            else {
                next_state = S30;
            }
            break;
        case S27:
            if (esponente.read()[7] == 0) {
                next_state = S28;
            }
            else {
                next_state = S29;
            }
            break;
        case S28:
            next_state = S18;
            break;
        case S29:
            next_state = S18;
            break;
        case S30:
            next_state = S31;
            break;
        case S31:
            if (t4.read() || t5.read()) {
                next_state = S32;
            }
            else {
                next_state = S33;
            }
            break;
        case S32:
            next_state = S33;
            break;
        case S33:
            if (mantissa.read()[24] == 1) {
                next_state = S25;
            }
            else {
                next_state = S19;
            }
            break;
        case S_Reset:
            next_state = S0;
            break;            
    }
}

void multiplier::datapath(void) {

    if (rst.read() == 1) {
        current_state = S_Reset;
    }
    else if (clk.read() == 1) {
        current_state = next_state;
        switch (next_state) {
            case S0:
                done.write(0);
                mantissa.write(0);
                moltiplicando.write(0);
                temp_mantissa.write(0);
                counter.write(0);                
                break;
            case S1:
                segno_op1.write(op.read()[31]);
                esponente_op1.write(op.read().range(30,23));
                mantissa_op1.write((1, op.read().range(22,0)));
                break;
            case S2:
                segno_op2.write(op.read()[31]);
                esponente_op2.write(op.read().range(30,23));
                mantissa_op2.write((1, op.read().range(22,0)));
                break;
            case S3:
                t1.write(esponente_op1.read() == 0);
                t2.write(esponente_op1.read() == 255);
                t3.write(esponente_op2.read() == 0);
                t4.write(esponente_op2.read() == 255);
                t5.write(mantissa_op1.read().range(22,0) == 0);
                t6.write(mantissa_op2.read().range(22,0) == 0);
                t7.write(esponente_op1.read() + esponente_op2.read());
                break;
            case S4:
                esponente.write(0);
                break;
            case S5:
                esponente.write(255);
                break;
            case S6:
                // empty
                break;
            case S7:
                esponente.write(0);
                break;
            case S8:
                esponente.write(255);
                break;
            case S9:
                esponente.write(t7.read() - 127);
                moltiplicando.write((0, mantissa_op1));
                break;
            case S10:
                eccezione.write(2);
                break;
            case S11:
                eccezione.write(1);
                break;
            case S12:
                eccezione.write(1);
                break;
            case S13:
                eccezione.write(3);
                break;
            case S14:
                eccezione.write(2);
                break;
            case S15:
                eccezione.write(1);
                break;
            case S16:
                eccezione.write(2);
                break;
            case S17:
                eccezione.write(1);
                break;
            case S18:
                result.write(0);
                done.write(1);
                eccezione_out.write(eccezione.read());
                break;
            case S19:
                result.write(((segno_op1.read() ^ segno_op2.read()), (esponente.read().range(7,0)), (mantissa.read().range(22,0))));
                done.write(1);
                eccezione_out.write(0);
                break;
            case S20:
                // empty
                break;
            case S21:
                // empty
                break;
            case S22:
                temp_mantissa.write(temp_mantissa.read() + moltiplicando.read());
                break;
            case S23:
                moltiplicando.write(moltiplicando.read() << 1);
                counter.write(counter.read() + 1);
                break;
            case S24:
                // empty
                break;
            case S25:
                esponente.write(esponente.read() +1);
                temp_mantissa.write(temp_mantissa.read() >> 1);
                break;
            case S26:
                mantissa.write((0, temp_mantissa.read().range(47,23)));
                break;
            case S27:
                // empty
                break;
            case S28:
                eccezione.write(4);
                break;
            case S29:
                eccezione.write(5);
                break;
            case S30:
                t1.write(temp_mantissa.read()[23] == 1);
                t2.write(temp_mantissa.read()[22] == 1);
                t3.write(temp_mantissa.read().range(21,0) == 0);
                break;
            case S31:
                t4.write(t1.read() && t2.read() && t3.read());
                t5.write(t2.read() && !t3.read());
                temp_mantissa.write(0);
                break;
            case S32:
                mantissa.write(mantissa.read() + 1);
                break;
            case S33:
                temp_mantissa.write((mantissa.read(),temp_mantissa.read().range(22, 0)));
                break;
            case S_Reset:
                eccezione.write(0);
                result.write(0);
                break;            
        }
    }
}