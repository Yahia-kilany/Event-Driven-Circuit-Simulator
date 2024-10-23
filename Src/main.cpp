#include <iostream>
#include "Gates.h"
#include "Circuit.h"
#include "ParseVerilog.h"
#include "ParseStim.h"

int main () {
    cout<<2;
    ParseVerilog parser;
    Circuit circuit = parser.parse ("parity_checker.v");
    circuit.simulate ();
    circuit.printValues ();


    return 0;
}