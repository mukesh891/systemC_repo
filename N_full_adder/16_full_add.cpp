#include <systemc.h>

SC_MODULE(FullAdder)
{
    sc_in<bool> a[16];
    sc_in<bool> b[16];
    sc_in<bool> cin;
    sc_out<bool> sum[16];
    sc_out<bool> cout;

    void add()
    {
        bool carry = cin.read();
        for(int i = 0; i < 16; i++)
        {
            bool s = (a[i].read() ^ b[i].read() ^ carry);
            sum[i].write(s);
            carry = ((a[i].read() & b[i].read()) | (a[i].read() & carry) | (b[i].read() & carry));
        }
        cout.write(carry);
    }

    SC_CTOR(FullAdder)
    {
        SC_METHOD(add);
        sensitive << a << b << cin;
    }
};

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> a[16];
    sc_signal<bool> b[16];
    sc_signal<bool> cin;
    sc_signal<bool> sum[16];
    sc_signal<bool> cout;

    FullAdder adder("adder");
    adder.a(a);
    adder.b(b);
    adder.cin(cin);
    adder.sum(sum);
    adder.cout(cout);

    for(int i = 0; i < 16; i++)
    {
        a[i].write(false);
        b[i].write(false);
        sum[i].write(false);
    }
    cin.write(false);

    sc_start();

    cout << "Results: " << endl;
    for(int i = 0; i < 16; i++)
    {
        cout << "sum[" << i << "]: " << sum[i] << endl;
    }
    cout << "carry_out: " << cout << endl;

    return 0;
}
