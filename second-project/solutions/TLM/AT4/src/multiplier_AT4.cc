#include "multiplier_AT4.hh"

tlm::tlm_sync_enum multiplier_AT4::nb_transport_fw(tlm::tlm_generic_payload & trans, tlm::tlm_phase & phase, sc_time & t) {
    if (pending_transaction != NULL) {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    if (phase != tlm::BEGIN_REQ) {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    cout << "\t\t[MULTIPLIER:] Received invocation of the nb_transport_fw primitive" << endl;
    cout << "\t\t[MULTIPLIER:] Activating the IOPROCESS" << endl;
    pending_transaction = &trans;
    ioDataStruct = *((iostruct*) trans.get_data_ptr());

    phase = tlm::END_REQ;

    io_event.notify();

    cout << "\t\t[MULTIPLIER:] End of the nb_transport_fw primitive" << endl;
    return tlm::TLM_UPDATED;
}

void multiplier_AT4::IOPROCESS() {
    sc_time timing_annotation;

    while (true) {
        wait(io_event);

        cout << "\t\t[MULTIPLIER:] IOPROCESS has been activated" << endl;

        wait(100, SC_NS);

        if(pending_transaction -> is_write()) {
            cout << "\t\t[MULTIPLIER:] Invoking the multiplication_function to calculate the floating point multiplication" << endl;
            multiplication_function();
        }
        else {
            cout << "\t\t[MULTIPLIER:] Returning result: " << ioDataStruct.result << endl;
        }

        pending_transaction -> set_response_status(tlm::TLM_OK_RESPONSE);

        *((iostruct*) pending_transaction -> get_data_ptr()) = ioDataStruct;
        tlm::tlm_phase phase = tlm::BEGIN_RESP;

        cout << "\t\t[MULTIPLIER:] Invoking the nb_transport_bw primitive - write" << endl;
        target_socket -> nb_transport_bw(*pending_transaction, phase, timing_annotation);

        pending_transaction = NULL;
    }
}

void multiplier_AT4::multiplication_function() {
    cout << "\t\t[MULTIPLIER:] Calculating multiplication_function ... " << endl;
    ioDataStruct.result = float(ioDataStruct.op1 * ioDataStruct.op2);
}

multiplier_AT4::multiplier_AT4 (sc_module_name name_): sc_module(name_), target_socket("target_socket"), pending_transaction(NULL) {
    target_socket(*this);
    SC_THREAD(IOPROCESS);
}

void multiplier_AT4::b_transport(tlm::tlm_generic_payload & trans, sc_time & t) {

}

bool multiplier_AT4::get_direct_mem_ptr(tlm::tlm_generic_payload & trans, tlm::tlm_dmi& dmi_data) {
    return false;
}

unsigned int multiplier_AT4::transport_dbg(tlm::tlm_generic_payload & trans){
    return 0;
}