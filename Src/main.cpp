#include <iostream>
#include "Gates.h"
#include "Circuit.h"
#include "ParseVerilog.h"
#include "ParseStim.h"
#include "event.h"
std::ostream& operator<<(std::ostream& os, const event& e) {
    os << e.time << " " << e.name << " " << e.value;
    return os;
}
int main(){
    ParseVerilog parser;
    Circuit circuit = parser.parse("./Tests/parity_checker.v");
    circuit.simulate();
    circuit.printValues();


    return 0;
}

