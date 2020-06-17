#include "systemc.h"

SC_MODULE(filter){

    sc_in <float> x;
    sc_out <float> y;
    sc_in_clk TestClk;
    sc_in <bool> reset;

    float a0, a1, a2, a3, a4, a5;
    sc_signal <float> R0out, R1out, R2out, R0in, R1in, R2in;

    void seq_proc(){
        while(1){
            if(reset.read() == true){
                R0out.write(0);
                R1out.write(0);
                R2out.write(0);
            }
            else{
                R0out.write(R0in.read());
                R1out.write(R1in.read());
                R2out.write(R2in.read());
            wait();
            }

        }
    }

    void comb_proc_1(){
        float xs = x.read();
        float R0s = R0out.read();
        float R1s = R1out.read();
        float R2s = R2out.read();

        R0in.write(xs + a0*R0s);     
        R1in.write(xs + a2*R1s + a4*R2s);
        R2in.write(R1s);
    }

    void comb_proc_2(){
        float R0s = R0out.read();
        float R1s = R1out.read();
        float R2s = R2out.read();   

        y.write(a1*R0s + a3*R1s + a5*R2s);
    }

    SC_CTOR(filter){
        SC_CTHREAD(seq_proc, TestClk.pos());
        SC_METHOD(comb_proc_1); sensitive << x << R0out << R1out << R2out;
        SC_METHOD(comb_proc_2); sensitive << TestClk.pos();

        a0 = 0.4; a1 = 0.24; a2 = -0.8, a3 = 0.2, a4 = -0.5, a5 = 0.25;
    }
};
