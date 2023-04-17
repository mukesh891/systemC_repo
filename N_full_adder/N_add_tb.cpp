#include <systemc.h>
#include "N_add.cpp" 
int sc_main(int argc, char* argv[]) {
  
  sc_trace_file* tf/* = sc_create_vcd_trace_file("trace")*/;
  const int N=16;
  sc_signal<bool> clk, rst;
  sc_signal<sc_lv<1>> a_sig[N];
  sc_signal<sc_lv<1>> b_sig[N];
  sc_signal<sc_lv<1>> sum_sig[N];
  sc_signal<sc_lv<1>> cin_sig, cout_sig;

  n_full_adder n_adder("n_adder");

  n_adder.clk(clk);
  n_adder.rst(rst);

  for(int i=0;i<N;i++){
  n_adder.a[i](a_sig[i]);
  n_adder.b[i](b_sig[i]);
  n_adder.sum[i](sum_sig[i]);
  }
  n_adder.cin(cin_sig);
  n_adder.caout(cout_sig);

 /* sc_trace_file* tf = sc_create_vcd_trace_file("trace");
  tf->set_time_unit(1, SC_NS);
  sc_trace(tf, clk, "clk");
  sc_trace(tf, rst, "rst");
  sc_trace(tf, a_sig, "a");
  sc_trace(tf, b_sig, "b");
  sc_trace(tf, cin_sig, "cin");
  sc_trace(tf, sum_sig, "sum");
  sc_trace(tf, cout_sig, "cout");
*/
  for(int i=0;i<N;i++){
  a_sig[i].write(rand()%2);
  b_sig[i].write(rand()%2);

 // wait(1, SC_NS);
  }
  cin_sig.write(rand()%2);

  sc_start(100, SC_NS);
  
  cout << "input a = ";
  for(int i=N-1;i>=0;i--){
  	cout << a_sig[i];
  }
  
  cout << "\n input b = ";
  for(int i=N-1;i>=0;i--){
  	cout << b_sig[i];
  }
  cout << "\n input cin = " << cin_sig << endl;
  

  cout << "\n OUTPUT : sum = ";
  for(int i=N-1;i>=0;i--){
  	cout << sum_sig[i];
  }
  cout << "\n OUTPUT : caout = " << cout_sig;

 // printf("a_sig=%0d",a_sig);
 // printf("b_sig=%0d",b_sig);
  //printf("sum_sig=%0d",sum_sig);
  //printf("caout=%0d",cout_sig);

	//cout << "Finished simulation time\t   " << "  " << a_sig.read() << "  " << b_sig.read() << "  " <<sum_sig.read() << "  " <<cout_sig.read() << "  " << sc_time_stamp() << endl;
  
  //cout << "Finished simulation time\t   " << "  " << a_sig.read() << "  " << b_sig.read() << "  " <<sum_sig.read() << "  " <<cout_sig.read() << "  " << sc_time_stamp() << endl;

  sc_bv<N> a_comb,b_comb,sum_comb;
  //updating all the tb signals
  //wait(0.01, SC_NS);
  for(int i=0;i<N;i++){
 	a_comb[i]=a_sig[i].read().get_bit(0);	
 	b_comb[i]=b_sig[i].read().get_bit(0);	
 	sum_comb[i]=sum_sig[i].read().get_bit(0);	
  }
  tf = sc_create_vcd_trace_file("waveform");

  //add signals to trace
  sc_trace(tf,clk,"clk");
  sc_trace(tf,rst,"rst");
  sc_trace(tf,a_comb,"a_comb");
  sc_trace(tf,b_comb,"b_comb");
  sc_trace(tf,cin_sig,"cin_sig");
  sc_trace(tf,sum_comb,"sum_comb");
  sc_trace(tf,cout_sig,"cout_sig");

  //wait(1, SC_NS);

  sc_close_vcd_trace_file(tf);

  return 0;
}

