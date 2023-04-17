#include <systemc.h>

SC_MODULE(half_adder) {
  sc_in<bool> clk, rst;      // input ports for a and b
  sc_in<sc_lv<1>> a, b;      // input ports for a and b
  sc_out<sc_lv<1>> sum;      // output port for sum
  sc_out<sc_lv<1>> caout;  // output port for carry-out

  SC_CTOR(half_adder) {
    SC_METHOD(add);
    sensitive << a << b ;
    sensitive << clk.pos() ;

  }

  void add() {
    sc_lv<1> a_val = a.read();
    sc_lv<1> b_val = b.read();
    sc_lv<1> sum_val = (a_val ^ b_val); 
    sc_lv<1> cout_val = (a_val & b_val);
    sum.write(sum_val);
    caout.write(cout_val);
  }
};
