#include "multiplier_UT.hh"

multiplier_UT::multiplier_UT(sc_module_name name_): sc_module(name_), target_socket("target_socket"), pending_transaction(NULL) {
  target_socket(*this);
}

void multiplier_UT::b_transport(tlm::tlm_generic_payload & trans, sc_time & t) {
  ioDataStruct = *((iostruct*) trans.get_data_ptr());

  if (trans.is_write()) {
    cout << "\t\t[MULTIPLIER:] Received invocation of the b_transport primitive - write" << endl;
    cout << "\t\t[MULTIPLIER:] Invoking the multiplication_function to calculate the floating point multiplication" << endl;
    
    multiplication_function();
    
    ioDataStruct.result = tmp_result;
    
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
    cout << "\t\t[MULTIPLIER:] Returning result: " << tmp_result << endl;
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
  } 
  else if (trans.is_read()) {
    cout << "\t\t[MULTIPLIER:] Received invocation of the b_transport primitive - read" << endl;

    ioDataStruct.result = tmp_result;

    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
    cout << "\t\t[MULTIPLIER:] Returning result: " << tmp_result << endl;
  }

}

void multiplier_UT::multiplication_function() {
  cout << "\t\t[MULTIPLIER:] Calculating multiplication_function ... " << endl;
  tmp_result = float(ioDataStruct.op1 * ioDataStruct.op2);
}

bool multiplier_UT::get_direct_mem_ptr (tlm::tlm_generic_payload & trans, tlm::tlm_dmi & dmi_data) {
  return false;
}

tlm::tlm_sync_enum multiplier_UT::nb_transport_fw(tlm::tlm_generic_payload & trans, tlm::tlm_phase & phase, sc_time & t) {
  return tlm::TLM_COMPLETED;
}

unsigned int multiplier_UT::transport_dbg(tlm::tlm_generic_payload & trans) {
  return 0;
}
