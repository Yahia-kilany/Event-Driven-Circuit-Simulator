#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../include/Gates.h"
#include "../include/Circuit.h"
#include "../include/ParseVerilog.h"
#include "../include/StimulusParser.h"

namespace fs = std::filesystem;

int main () {
    std::string testDir = "../Tests/";
    std::string verilogPath;
    std::string stimulusPath;

    // Prompt user for Verilog file path or use default
    std::cout << "Enter the path for the Verilog file (default: All the files in .\\Tests): " << endl;
    std::getline (std::cin , verilogPath);
    // Prompt user for stimulus file path or use default
    std::cout << "Enter the path for the stimulus file (default: All the files in .\\Tests): " << endl;
    std::getline (std::cin , stimulusPath);

    if (verilogPath.empty () && stimulusPath.empty ()) {
        // Loop through all files in the tests directory if defaults are used
        for (const auto& entry : fs::directory_iterator (testDir)) {
            if (entry.is_regular_file ()) {
                std::string filePath = entry.path ().string ();

                // Check if the file is a Verilog file (.v)
                if (filePath.find (".v") != std::string::npos) {
                    // Derive stimulus file path by replacing the extension with ".stim"
                    std::string currentStimulusPath = filePath.substr (0 , filePath.find_last_of (".")) + ".stim";

                    // Check if the corresponding .stim file exists
                    if (fs::exists (currentStimulusPath)) {
                        std::cout << "Processing Verilog file: " << filePath << std::endl;
                        std::cout << "Using stimulus file: " << currentStimulusPath << std::endl;

                        // Parse Verilog file and create circuit
                        Circuit circuit = parseVerilog (filePath);

                        // Parse stimulus file and fill event queue
                        std::vector<Event> events = parseStimFile (currentStimulusPath);
                        circuit.fillEventQueue (events);

                        // Simulate the circuit
                        circuit.simulate ();
                        std::cout << "Simulation completed for: " << filePath << "\n" << std::endl;
                    }
                    else {
                        std::cerr << "Warning: Stimulus file not found for " << filePath << std::endl;
                    }
                }
            }
        }
    }
    else {
        // Parse Verilog file and create circuit for user-provided paths
        std::cout << "Processing Verilog file: " << verilogPath << std::endl;
        std::cout << "Using stimulus file: " << stimulusPath << std::endl;
        Circuit circuit = parseVerilog (verilogPath);

        // Parse stimulus file and fill event queue
        std::vector<Event> events = parseStimFile (stimulusPath);
        circuit.fillEventQueue (events);

        // Simulate the circuit
        circuit.simulate ();
        std::cout << "Simulation completed for: " << verilogPath << "\n" << std::endl;
    }

    return 0;
}
