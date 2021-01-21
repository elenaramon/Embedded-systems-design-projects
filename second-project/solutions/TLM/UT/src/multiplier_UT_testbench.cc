#include "multiplier_UT_testbench.hh"

void multiplier_UT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) {
  
}

tlm::tlm_sync_enum multiplier_UT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t) {
  return tlm::TLM_COMPLETED;
}

void multiplier_UT_testbench::run() {

  sc_time local_time;
  iostruct multiplier_packet;
  tlm::tlm_generic_payload payload;	

  for (int i = 0; i < 20; i++) {

    multiplier_packet.op1 = (float(rand() / float(RAND_MAX)));
    multiplier_packet.op2 = (float(rand() / float(RAND_MAX)));
    cout << "[TB:] Calculating the floating point multiplication between " << multiplier_packet.op1 << " and " << multiplier_packet.op2 <<endl;
    payload.set_data_ptr((unsigned char*) &multiplier_packet);
    payload.set_address(0);
    payload.set_write();

    cout << "[TB:] Invoking the b_transport primitive - write" << endl;
    initiator_socket -> b_transport(payload, local_time);

    if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) {
      cout << "[TB:] TLM protocol correctly implemented" << endl;
      cout << "[TB:] Result is: " << multiplier_packet.result << endl;
    }

  }
  sc_stop();
}

multiplier_UT_testbench::multiplier_UT_testbench(sc_module_name name): sc_module(name) {

  initiator_socket(*this);
  SC_THREAD(run);

}
