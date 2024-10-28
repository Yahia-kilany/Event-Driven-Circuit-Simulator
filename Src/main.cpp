#include <iostream>
#include "Gates.h"
#include "Circuit.h"
#include "ParseVerilog.h"
#include "ParseStim.h"
#include "Event.h"
std::string removeCharacters (const std::string& input , const std::string& charsToRemove) {
    std::string result = input;
    result.erase (std::remove_if (result.begin () , result.end () ,
        [&](char c) { return charsToRemove.find (c) != std::string::npos; }) ,
        result.end ());
    return result;
}

std::ostream& operator<<(std::ostream& os, const Event& e) {
    os <<"#" <<e.time << " " << e.name << " " << e.value;
    return os;
}
int main(){
    ParseVerilog parser;
    Circuit circuit = parser.parse("./Tests/parity_checker.v");
    circuit.simulate();
    circuit.printValues();


    return 0;
}

