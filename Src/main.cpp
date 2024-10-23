#include <iostream>
#include "Gates.h"
#include "Circuit.h"
#include "ParseVerilog.h"
#include "ParseStim.h"

int main(){
    ParseVerilog parser;
    Circuit circuit = parser.parse(".\\Tests\\parity_checker.v");
    circuit.simulate();
    circuit.printValues();

    std::vector<std::map<std::string, int>> stimuli = parseStimFile(".\\Tests\\parityChecker.stim");
    for (const auto& stimulus : stimuli) {
        for (const auto& [name, value] : stimulus) {
            std::cout << name << ": " << value << std::endl;
        }
    }

    return 0;
}

