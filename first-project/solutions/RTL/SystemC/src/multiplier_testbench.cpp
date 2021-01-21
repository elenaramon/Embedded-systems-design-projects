#include "systemc.h"
#include <stdlib.h>
#include <time.h>
#include "multiplier_testbench.h"

void multiplier_testbench::clk_gen(void) {
    while(true) {
        clk.write(1);
        wait(PERIOD / 2, sc_core::SC_NS);

        clk.write(0);
        wait(PERIOD / 2, sc_core::SC_NS);
    }
}

void multiplier_testbench::run(void) {

    sc_uint<32> operator_rand;

    srand(time(NULL));

    rst.write(1);

    wait();    

    for(int i = 0; i < 20; i++) {

        cout << "Calcolo del " << i << "-esimo prodotto" << endl;

        rst.write(0);

        wait();
        
        ready.write(1);

        op1_out.write(((rand() % 2), sc_uint<31>(rand() % 2147483648)));
        op2_out.write(((rand() % 2), sc_uint<31>(rand() % 2147483648)));

        wait();

        op1_out.write(((rand() % 2), sc_uint<31>(rand() % 2147483648)));
        op2_out.write(((rand() % 2), sc_uint<31>(rand() % 2147483648)));

        wait();

        ready.write(0);

        while (done.read() != 1) {
            wait();
        }

        segno_in_1.write(result.read()[31]);
        esponente_in_1.write(result.read()(30,23));
        mantissa_in_1.write(result.read()(22,0));
        eccezione_in_1.write(eccezione_in.read());

        wait();

        cout << "Risultato 1 " << endl;
        cout << " " << segno_in_1;
        cout << " " << esponente_in_1;
        cout << " " << mantissa_in_1;
        cout << " " << eccezione_in_1 << endl;

        segno_in_2.write(result.read()[31]);
        esponente_in_2.write(result.read()(30,23));
        mantissa_in_2.write(result.read()(22,0));
        eccezione_in_2.write(eccezione_in.read());

        wait();    

        cout << "Risultato 2 " << endl;
        cout << " " << segno_in_2;
        cout << " " << esponente_in_2;
        cout << " " << mantissa_in_2;
        cout << " " << eccezione_in_2 << endl;

        rst.write(1);
        op1_out.write(0);
        op2_out.write(0);

        wait();
    }

    rst.write(0);
    wait();
    ready.write(1);

    operator_rand = (((rand() % 2), sc_uint<31>(rand() % 2147483648)));

    cout << "Calcolo ultimo prodotto tra " << operator_rand << endl;
    op1_out.write(operator_rand);
    op2_out.write(operator_rand);

    wait();

    operator_rand = (((rand() % 2), sc_uint<31>(rand() % 2147483648)));

    cout << "E " << operator_rand << endl;
    op1_out.write(operator_rand);
    op2_out.write(operator_rand);

    wait();

    ready.write(0);

    while (done.read() != 1) {
        wait();
    }

    segno_in_1.write(result.read()[31]);
    esponente_in_1.write(result.read()(30,23));
    mantissa_in_1.write(result.read()(22,0));
    eccezione_in_1.write(eccezione_in.read());

    wait();

    cout << "Risultato 1 " << endl;
    cout << " " << segno_in_1;
    cout << " " << esponente_in_1;
    cout << " " << mantissa_in_1;
    cout << " " << eccezione_in_1 << endl;

    segno_in_2.write(result.read()[31]);
    esponente_in_2.write(result.read()(30,23));
    mantissa_in_2.write(result.read()(22,0));
    eccezione_in_2.write(eccezione_in.read());

    wait();    

    cout << "Risultato 2 " << endl;
    cout << " " << segno_in_2;
    cout << " " << esponente_in_2;
    cout << " " << mantissa_in_2;
    cout << " " << eccezione_in_2 << endl;


    if (segno_in_1.read() == segno_in_2.read()) {
        match_segno.write(1);
    }
    else {
        match_segno.write(0);
    }
    if (esponente_in_1.read() == esponente_in_2.read()) {
        match_esponente.write(1);
    }
    else {
        match_esponente.write(0);
    }
    if (mantissa_in_1.read() == mantissa_in_2.read()) {
        match_mantissa.write(1);
    }
    else {
        match_mantissa.write(0);
    }
    if (eccezione_in_1.read() == eccezione_in_2.read()) {
        match_eccezione.write(1);
    }
    else {
        match_eccezione.write(0);
    }

    rst.write(1);
    ready.write(0);
    op1_out.write(0);
    op2_out.write(0);
    sc_stop();
}
