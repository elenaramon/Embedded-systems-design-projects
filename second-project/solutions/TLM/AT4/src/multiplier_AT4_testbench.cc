#include "multiplier_AT4_testbench.hh"

void multiplier_AT4_testbench::run() {
    sc_time local_time = SC_ZERO_TIME;
    iostruct multiplier_packet;
    tlm::tlm_generic_payload payload;

    for (int i = 0; i < 20; i++) {

        multiplier_packet.op1 = (float(rand() / float(RAND_MAX)));
        multiplier_packet.op2 = (float(rand() / float(RAND_MAX)));
        cout << "[TB:] Calculating the floating point multiplication between " << multiplier_packet.op1 << " and " << multiplier_packet.op2 << endl;

        tlm::tlm_phase phase = tlm::BEGIN_REQ;

        payload.set_address(0);
        payload.set_data_ptr((unsigned char*) &multiplier_packet);
        payload.set_write();

        cout << "[TB:] Invoking the nb_transport_fw primitive of multiplier - write" << endl;
        tlm::tlm_sync_enum result = initiator_socket -> nb_transport_fw(payload, phase, local_time);

        if (result == tlm::TLM_COMPLETED) {
            cout << "[ERROR:] Transaction error on nb_transport_fw. Forcing simulation stop." << endl;
            sc_stop();
        }

        if (phase != tlm::END_REQ) {
            cout << "[ERROR:] Unexpected protocol phase on nb_transport_fw. Forcing simulation stop." << endl;
            sc_stop();
        }

        cout << "[TB:] Waiting for nb_trasnport_fw to be invoked" << endl;
        response_pending = true;
        wait(available_response);
        
        response_pending = false;

        phase = tlm::BEGIN_REQ;
        payload.set_address(0);
        payload.set_data_ptr((unsigned char*) &multiplier_packet);
        payload.set_read();

        cout << "[TB:] Invoking the nb_trasnport_fw primitive of multiplier - read" << endl;
        result = initiator_socket -> nb_transport_fw(payload, phase, local_time);

        if (result == tlm::TLM_COMPLETED) {
            cout << "[ERROR:] Invoking the nb_transport_fw. Forcing simulation stop." << endl;
            sc_stop();
        }

        if (phase != tlm::END_REQ) {
            cout << "[ERROR:] Unexpected protocol phase on nb_trasnport_fw. Forcing simulation stop." << endl;
            sc_stop();
        }

        cout << "[TB:] Waiting for nb_transport_bw to be invoked" << endl;
        response_pending = true;
        wait(available_response);

        response_pending = false;

        if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) {
            cout << "[TB:] TLM protocol correctly implemented" << endl;
            cout << "[TB:] Result is: " << multiplier_packet.result << endl;
        }

    }

    sc_stop();    
}

tlm::tlm_sync_enum multiplier_AT4_testbench::nb_transport_bw (tlm::tlm_generic_payload & trans, tlm::tlm_phase & phase, sc_time & t) {

    if (!response_pending) {
        cout << "[ERROR:] Unexpected state for nb_transport_bw" << endl;
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    if (phase != tlm::BEGIN_RESP) {
        cout << "[ERROR:] Unexpected phase for nb_transport_bw" << endl;
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    available_response.notify();

    phase = tlm::END_RESP;

    return tlm::TLM_COMPLETED;
}

multiplier_AT4_testbench::multiplier_AT4_testbench(sc_module_name name): sc_module(name), response_pending(false) {
    initiator_socket(*this);
    SC_THREAD(run);
}

void multiplier_AT4_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) {

}