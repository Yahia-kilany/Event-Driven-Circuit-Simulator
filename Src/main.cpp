#include <iostream>
#include <string>
#include <vector>
#include "../include/Gates.h"
#include "../include/Circuit.h"
#include "../include/ParseVerilog.h"
#include "../include/StimulusParser.h"

int main () {
    std::string verilogPath;
    std::string stimulusPath;

    // Prompt user for Verilog file path or use default
    std::cout << "Enter the path for the Verilog file (default: ../Tests/parity_checker.v): ";
    std::getline(std::cin, verilogPath);
    if (verilogPath.empty()) {
        verilogPath = "../Tests/parity_checker.v";  // Default path
    }

    // Prompt user for stimulus file path or use default
    std::cout << "Enter the path for the stimulus file (default: ../Tests/parity_checker.stim): ";
    std::getline(std::cin, stimulusPath);
    if (stimulusPath.empty()) {
        stimulusPath = "../Tests/parity_checker.stim";  // Default path
    }

    // Parse Verilog file and simulate
    Circuit circuit = parseVerilog(verilogPath);
    circuit.simulate();

    // Parse stimulus file and fill event queue
    std::vector<Event> events = parseStimFile(stimulusPath);
    circuit.fillEventQueue(events);
    circuit.simulate();

    return 0;
}
