#include "ParseVerilog.h"
std::string removeCharacters (const std::string& input , const std::string& charsToRemove) {
    std::string result = input; // Copy the input string to result

    // Use std::remove_if and erase to remove unwanted characters
    result.erase (std::remove_if (result.begin () , result.end () ,
        [&](char c) { return charsToRemove.find (c) != std::string::npos; }) ,
        result.end ());

    return result; // Return the modified string
}
Circuit ParseVerilog::parse (const std::string& filename) {
    const std::string charsToRemove = "(),; ";

    Circuit circuit;
    std::ifstream file (filename);
    if (!file.is_open ()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return circuit; // Return empty circuit
    }

    std::unordered_map<string , Wire*> wires;
    std::string line;
    while (std::getline (file , line)) {
        std::istringstream iss (line);
        std::string token;

        if (line.find ("input") != std::string::npos || line.find ("output") != std::string::npos || line.find ("wire") != std::string::npos) {
            while (iss >> token) {
                if (token != "input" && token != "output" && token != "wire" && token != ";" && token != "(" && token != ")") {
                    token = removeCharacters (token , charsToRemove);
                    std::cout << "Wire: " << token << std::endl; // Indicate wire creation
                    Wire* w = circuit.addWire (token);
                    wires[token] = w; // Store wire in map
                }
            }
        }
        else {
            std::string gate_type , gate_name;
            if (line.find ("AND") != std::string::npos || line.find ("OR") != std::string::npos || line.find ("NAND") != std::string::npos
                || line.find ("NOR") != std::string::npos || line.find ("XOR") != std::string::npos ||
                line.find ("XNOR") != std::string::npos) {

                iss >> gate_type >> gate_name;
                iss.ignore (); // Ignore the opening parenthesis

                std::vector<Wire*> ports;
                while (iss >> token) {
                    if (token != "(" && token != ")" && token != "," && token != ";") {
                        token = removeCharacters (token , charsToRemove);
                        if (wires.find (token) != wires.end ()) {
                            ports.push_back (wires[token]);
                            std::cout << "Input: " << token << std::endl; // Indicate ports for gate
                        }
                        else {
                            std::cerr << "Error: Wire " << token << " not found." << std::endl;
                        }
                    }
                }

                Wire* output = ports[0];
                std::vector<Wire*> inputs(ports.begin() + 1, inputs.end());

                Gate* gate = new Gate (inputs , output , gate_type);
                circuit.addGate(gate);
            }
        }
    }
    return circuit;
}