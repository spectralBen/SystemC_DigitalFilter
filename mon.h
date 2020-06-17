#include "systemc.h"
#include <iomanip>
using namespace std;

SC_MODULE(mon){
  sc_in<float> x, y;
  sc_in<bool> reset, TestClk;
  sc_signal <float> R0out, R1out, R2out, R0in, R1in, R2in;

  void monitor(){
	cout << setw(15) << "Time";
	cout << setw(15) << "x" << setw(15) << "reset";
	cout << setw(15) << "y" << endl;
	
	while (true){
		cout << setw(15) << sc_time_stamp();
		cout << setw(15) << x.read() << setw(15) << reset.read();
		cout << setw(15) << y.read() << endl;

		wait();		
	}
  }
  SC_CTOR(mon){

    SC_CTHREAD(monitor, TestClk.pos());
  }
};

