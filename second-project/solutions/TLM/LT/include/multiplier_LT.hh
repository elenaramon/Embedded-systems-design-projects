#ifndef __multiplier_LT_HPP__
#define __multiplier_LT_HPP__

#include <systemc.h>
#include <tlm.h>
#include "define_LT.hh"

class multiplier_LT: public sc_module, public virtual tlm::tlm_fw_transport_if<> {

 public:
  
  tlm::tlm_target_socket<> target_socket;

  virtual void b_transport(tlm::tlm_generic_payload & trans, sc_time & t);
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload & trans, tlm::tlm_dmi & dmi_data);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload & trans);
  
  void end_of_elaboration(); 
  void reset(); 
  
  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload & trans, tlm::tlm_phase & phase, sc_time & t);

  iostruct  ioDataStruct;
  tlm::tlm_generic_payload* pending_transaction;
  float tmp_result;
  sc_time timing_annotation;

  void multiplication_function();

  SC_HAS_PROCESS(multiplier_LT);

  multiplier_LT(sc_module_name name_);
  
};

#endif

