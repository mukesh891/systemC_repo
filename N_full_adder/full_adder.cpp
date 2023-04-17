#include <systemc.h>
#include "half_adder.cpp"

SC_MODULE(full_adder){

	sc_in<bool> clk,rst;
	sc_in<sc_lv<1>> a,b,cin;
	sc_out<sc_lv<1>> sum,caout;
	sc_signal<sc_lv<1>> sum1,c1,c2;

	half_adder *ha1;
	half_adder *ha2;

	SC_CTOR(full_adder){
	ha1 = new half_adder(sc_gen_unique_name("ha1"));
	ha1->a(a);
	ha1->b(b);
	ha1->sum(sum1);
	ha1->caout(c1);
	ha1->clk(clk);
	ha1->rst(rst);


	ha2 = new half_adder(sc_gen_unique_name("ha2"));
	ha2->a(sum1);
	ha2->b(cin);
	ha2->sum(sum);
	ha2->caout(c2);
	ha2->clk(clk);
	ha2->rst(rst);
	
	SC_METHOD(c_out);
    		sensitive << c1 << c2 ;
	}
	void c_out(){
		caout.write(c1.read() | c2.read());
	
	}
};
