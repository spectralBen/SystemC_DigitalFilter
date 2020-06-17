#include "systemc.h"
#include "stim.h"
#include "filter.h"
#include "mon.h"

int sc_main(int argc, char* argv[]){

    sc_signal <float> x_sig, y_sig;
    sc_signal <bool> reset_sig;
    sc_clock TestClk("TestClock", 10, SC_NS, 0.5, 1, SC_NS);
  
    stim Stim1("Stimulus");
    Stim1.x(x_sig);
    Stim1.reset(reset_sig);
    Stim1.TestClk(TestClk);
   
    filter filter("filter");
    filter.x(x_sig);
    filter.reset(reset_sig);
    filter.y(y_sig);
    filter.TestClk(TestClk);

    
    mon Monitor1("Monitor");
    Monitor1.x(x_sig);
    Monitor1.reset(reset_sig);
    Monitor1.y(y_sig);
    Monitor1.TestClk(TestClk); 
  
    sc_trace_file* Tf = sc_create_vcd_trace_file("system_traces");
    Tf->set_time_unit(1, SC_NS);
    sc_trace(Tf, x_sig  , "x" );
    sc_trace(Tf, reset_sig  , "reset" );
    sc_trace(Tf, y_sig  , "y" );
    sc_trace(Tf, filter.R0in, "R1in");
    sc_trace(Tf, filter.R1in, "R2in");
    sc_trace(Tf, filter.R2in, "R3in");
    sc_trace(Tf, filter.R0out, "R1out");
    sc_trace(Tf, filter.R1out, "R2out");
    sc_trace(Tf, filter.R2out, "R3out");

    sc_start(120, SC_NS);
    sc_close_vcd_trace_file(Tf);
  
    return 0;
}
