#include <systemc.h>
#include "full_adder.cpp"

SC_MODULE(n_full_adder){
	sc_in<bool> clk,rst;
	
	sc_in<sc_lv<1>> a[16];
	sc_in<sc_lv<1>> b[16];
	sc_in<sc_lv<1>> cin;
	
	sc_out<sc_lv<1>> sum[16];
	sc_out<sc_lv<1>> caout;
	
	sc_signal<sc_lv<1>> sum1;
	sc_signal<sc_lv<1>> c[16];

	full_adder *nfa[16];

	SC_CTOR(n_full_adder){
	for(int i=0;i<16;i++){
	nfa[i] = new full_adder(sc_gen_unique_name("nfa"));
	nfa[i]->a(a[i]);
	nfa[i]->b(b[i]);
	if(i==0){
		nfa[i]->cin(cin);
	}
	else {
		nfa[i]-> cin(c[i]);
	}
	nfa[i]->sum(sum[i]);
	if(i==15){
		nfa[i]->caout(caout);
	}
	else{
		nfa[i]-> caout(c[i+1]);
	}

	nfa[i]->clk(clk);
	nfa[i]->rst(rst);
	} 
	}
};


