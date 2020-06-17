#include "systemc.h"
#include <iomanip>

SC_MODULE(stim){
    
    sc_out <float> x;
    sc_in_clk TestClk;
    sc_out <bool> reset;

  void stimgen(){

    reset.write(true);
    wait();
    reset.write(false);    
    x.write(1);
    wait();
    x.write(0);
    wait();
    wait();
    wait();
  }

  SC_CTOR(stim){
    
    SC_CTHREAD(stimgen, TestClk.pos());
  }
};


