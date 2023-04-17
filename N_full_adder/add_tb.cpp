#include <systemc.h>
#include "full_adder.cpp" 
int sc_main(int argc, char* argv[]) {
  sc_signal<sc_lv<1>> a_sig, b_sig, sum_sig,cin_sig, cout_sig;
  full_adder adder("adder");

  adder.a(a_sig);
  adder.b(b_sig);
  adder.cin(cin_sig);
  adder.sum(sum_sig);
  adder.caout(cout_sig);

  sc_trace_file* tf = sc_create_vcd_trace_file("trace");
  tf->set_time_unit(1, SC_NS);
  sc_trace(tf, a_sig, "a");
  sc_trace(tf, b_sig, "b");
  sc_trace(tf, cin_sig, "cin");
  sc_trace(tf, sum_sig, "sum");
  sc_trace(tf, cout_sig, "cout");

  for(int i=0;i<10;i++){
  a_sig.write(rand()%2);
  b_sig.write(rand()%2);
 cin_sig.write(rand()%2);

  sc_start(1, SC_NS);
  cout << "Finished simulation time\t   " << "  " << a_sig.read() << "  " << b_sig.read() << "  " <<sum_sig.read() << "  " <<cout_sig.read() << "  " << sc_time_stamp() << endl;
  }

  sc_close_vcd_trace_file(tf);

  return 0;
}
