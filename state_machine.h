#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>
using namespace std;
// TODO

enum base {Start, G, GA, GAA, GAAG};

SC_MODULE(stateMachine) {

    sc_in<char> input;
    sc_in<bool> clk;
    base state;
    unsigned int G_pos;
    unsigned int counter;
    unsigned int position;

    int *posArray = (int*)calloc(10, sizeof(int));

    public:

    SC_HAS_PROCESS(stateMachine);               //SC_CTOR(statemachine)
    stateMachine(const sc_module_name &name);   //SC_CTOR(statemachine)

    void process();
    unsigned int getCount();
    void printPositions();
    void end_of_simulation();

};

#endif // STATE_MACHINE_H


