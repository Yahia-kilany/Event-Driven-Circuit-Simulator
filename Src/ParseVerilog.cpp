#include "../include/ParseVerilog.h"

Circuit parseVerilog(const std::string& filename) {
    const std::string charsToRemove = "(),;# "; // Characters to strip from tokens
    Circuit circuit; // Circuit object to store parsed wires and gates
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return circuit;
    }

    std::unordered_map<std::string, Wire*> wires; // Stores all wires by name
    std::string line;
    bool moduleFound = false; // Flag to track if "module" keyword has been found
    std::string moduleName; // Stores the module name

    // Process each line in the Verilog file
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        // Parse module name and ports
        if (!moduleFound && line.find("module") != std::string::npos) {
            moduleFound = true;
            iss >> token; // Ignore "module"
            getline(iss, moduleName, '('); // Extract the module name
            cout << "module name:" << moduleName << endl;
            circuit.setModuleName(moduleName); // Set the module name in the circuit
            // Parse each port of the module
            while (iss >> token) {
                token = removeCharacters(token, charsToRemove); // Remove unwanted characters
                cout << "port:" << token << endl;
                Wire* w = circuit.addWire(token); // Add wire to the circuit
                wires[token] = w; // Store wire in the map
            }
        }

        // Parse input, output, or wire declarations
        if (line.find("input") != std::string::npos || line.find("output") != std::string::npos || line.find("wire") != std::string::npos) {
            std::string name, wireType;
            iss >> wireType; // Get the wire type (input, output, or wire)
            wireType = removeCharacters(wireType, charsToRemove); // Clean up wire type
            iss >> name; // Get the wire name
            name = removeCharacters(name, charsToRemove); // Clean up wire name

            // Check if wire is already declared in the module header
            if ((wireType == "input" || wireType == "output") && !(wires.find(name) != wires.end())) {
                std::cerr << "Error: input/output wire " << name << " not declared in header." << std::endl;
            } else if (wireType == "wire") {
                Wire* w = circuit.addWire(name); // Add new wire
                w->type = wireType;
                wires[name] = w;
                std::cout << wireType << " : " << name << std::endl;
            } else {
                wires[name]->type = wireType; // Assign type to existing wire
                std::cout << wireType << " : " << name << std::endl;
            }
        } else { 
            // Parse gate declarations
            std::string gate_type, gate_name, gate_delay, temp;
            int delay = 0;

            // Check if the line contains a gate keyword
            if (line.find("and") != std::string::npos || line.find("or") != std::string::npos ||
                line.find("nand") != std::string::npos || line.find("nor") != std::string::npos ||
                line.find("xor") != std::string::npos || line.find("xnor") != std::string::npos ||
                line.find("buf") != std::string::npos || line.find("not") != std::string::npos) {

                iss >> gate_type; // Get gate type
                getline(iss, temp, '('); // Extract gate delay and name if present

                // Check for a delay specified with '#'
                if (temp.find('#') != std::string::npos) {
                    iss >> gate_delay;
                    gate_delay = removeCharacters(gate_delay, charsToRemove);
                    try {
                        delay = std::stoi(gate_delay); // Parse delay value
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Error: Invalid delay format in gate " << gate_type << std::endl;
                        continue;
                    }
                    getline(iss, gate_name, '('); // Get gate name
                } else {
                    gate_name = temp;
                }

                std::cout << gate_name << ' ' << gate_delay << " " << gate_type << std::endl;

                // Parse gate ports
                std::vector<Wire*> ports;
                while (iss >> token) {
                    token = removeCharacters(token, charsToRemove); // Clean up token
                    if (!token.empty() && wires.find(token) != wires.end()) {
                        ports.push_back(wires[token]);
                        std::cout << "Gate Port: " << token << std::endl;
                    } else {
                        std::cerr << "Error: Wire " << token << " not found." << std::endl;
                    }
                }

                // Create gate and connect ports if valid
                if (!ports.empty()) {
                    Wire* output = ports[0];
                    std::vector<Wire*> inputs(ports.begin() + 1, ports.end());
                    Gate* gate = new Gate(inputs, output, gate_type, delay);

                    // Add gate to each input wire's endGates list
                    for (auto& input : inputs) {
                        input->addGate(gate);
                    }
                    circuit.addGate(gate); // Add gate to circuit
                }
            }
        }
    }
    return circuit; // Return the populated circuit
}
