#ifndef __multiplier_UT_HPP__
#define __multiplier_UT_HPP__

#include <systemc.h>
#include <tlm.h>
#include "define_UT.hh"

class multiplier_UT: public sc_module, public virtual tlm::tlm_fw_transport_if<> {

 public:

  tlm::tlm_target_socket<> target_socket;

  virtual void b_transport(tlm::tlm_generic_payload & trans, sc_time & t);

  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload & trans, tlm::tlm_dmi & dmi_data);
  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload & trans, tlm::tlm_phase & phase, sc_time & t);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload & trans);

  iostruct  ioDataStruct;
  tlm::tlm_generic_payload* pending_transaction;
  float tmp_result;

  void multiplication_function();

  SC_HAS_PROCESS(multiplier_UT);
  multiplier_UT(sc_module_name name_);
  
};

#endif

