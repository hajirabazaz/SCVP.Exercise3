#include <iostream>

#include "state_machine.h"

using namespace std;

stateMachine::stateMachine(const sc_module_name &name) : sc_module(name) {
        state = Start;
        counter = 0;
        position = 0;
        G_pos = 0;
        SC_METHOD(process);
        sensitive << clk.pos();
        dont_initialize();
    }

void stateMachine::process(){
    position++;
    switch (state)
    {
    case Start:
        if (input == 'G')
            state = G;
        else
            state = Start;
        break;

    case G:
        G_pos = 1;
        if (input == 'A')
            state = GA;
        else if (input == 'G')
            state = G;
        else
            state = Start;            
        break;

    case GA:
        G_pos++;
        if (input == 'A')
            state = GAA;
        else if (input == 'G')
            state = G;                
        else
            state = Start;            
        break;            

    case GAA:
        G_pos++;
        if (input == 'G')
            state = GAAG;
        else if (input == 'A')  // For Regex /GA{2,}+G/
            state = GAA;
        else
            state = Start;            
        break;            

    case GAAG:
        G_pos++;
        posArray[counter] = position - G_pos;
        counter++;
        cout << "Pattern detected at position " << position-G_pos <<endl;
        cout << "Detection count: " << counter << endl <<endl;
        if (input == 'G')
            state = G;
        else if (input == 'A')
            state = GA;
        else
            state = Start;            
        break;            

    default:
        break;
    }
}

unsigned int stateMachine::getCount(){
    return counter;
}

void stateMachine::printPositions(){
    cout << "Pattern detected at positions:";
    int i = 0;
    while (posArray[i] != 0)
    {
        cout << " " << posArray[i++];
    }
    cout << endl << endl;
}
    
void stateMachine::end_of_simulation(){
    cout << "\nDetection frequency: " << getCount() << endl;
    printPositions();
}