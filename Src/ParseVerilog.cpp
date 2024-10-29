#include "ParseVerilog.h"

Circuit ParseVerilog::parse (const std::string& filename) {
    const std::string charsToRemove = "(),;# ";
    Circuit circuit;
    std::ifstream file (filename);
    if (!file.is_open ()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return circuit;
    }

    std::unordered_map<std::string , Wire*> wires;
    std::string line;
    bool moduleFound = false;
    std::string moduleName;

    while (std::getline (file , line)) {
        std::istringstream iss (line);
        std::string token;

        if (!moduleFound && line.find ("module") != std::string::npos) {
            moduleFound = true;
            iss >> token; // Ignore "module"
            getline (iss , moduleName , '(');
            cout << "module name:" << moduleName << endl;
            while (iss >> token) {
                token = removeCharacters (token , charsToRemove);
                cout << "port:" << token << endl;
                Wire* w = circuit.addWire (token);
                wires[token] = w;
            }
        }
        if (line.find ("input") != std::string::npos || line.find ("output") != std::string::npos || line.find ("wire") != std::string::npos) {
            std::string name , wireType;
            iss >> wireType;
            wireType = removeCharacters (wireType , charsToRemove);
            iss >> name;
            name = removeCharacters (name , charsToRemove);

            if ((wireType == "input" || wireType == "output") && !(wires.find (name) != wires.end ())) {
                std::cerr << "Error: input/output wire " << name << " not declared in header." << std::endl;
            }
            else if (wireType == "wire") {
                Wire* w = circuit.addWire (name);
                w->type = wireType;
                wires[name] = w;
                std::cout << wireType << " : " << name << std::endl;

            }
            else {
                wires[name]->type = wireType;
                std::cout << wireType << " : " << name << std::endl;
            }
        }
        else {
            std::string gate_type , gate_name , gate_delay , temp;
            int delay = 0;

            if (line.find ("and") != std::string::npos || line.find ("or") != std::string::npos ||
                line.find ("nand") != std::string::npos || line.find ("nor") != std::string::npos ||
                line.find ("xor") != std::string::npos || line.find ("xnor") != std::string::npos ||
                line.find ("buf") != std::string::npos || line.find ("not") != std::string::npos) {

                iss >> gate_type;
                getline (iss , temp , '(');

                if (temp.find ('#') != std::string::npos) {  // Check for delay
                    iss >> gate_delay;
                    gate_delay = removeCharacters (gate_delay , charsToRemove);
                    try {
                        delay = std::stoi (gate_delay);
                    }
                    catch (const std::invalid_argument&) {
                        std::cerr << "Error: Invalid delay format in gate " << gate_type << std::endl;
                        continue;
                    }
                    getline (iss , gate_name , '(');
                }
                else {
                    gate_name = temp;
                }

                std::cout << gate_name << ' ' << gate_delay << " " << gate_type << std::endl;

                // Parsing gate ports
                std::vector<Wire*> ports;
                while (iss >> token) {

                    token = removeCharacters (token , charsToRemove);
                    if (!token.empty () && wires.find (token) != wires.end ()) {
                        ports.push_back (wires[token]);
                        std::cout << "Gate Port: " << token << std::endl;
                    }
                    else {
                        std::cerr << "Error: Wire " << token << " not found." << std::endl;
                    }
                }

                // Create and add gate if ports are valid
                if (!ports.empty ()) {
                    Wire* output = ports[0];
                    std::vector<Wire*> inputs (ports.begin () + 1 , ports.end ());
                    Gate* gate = new Gate (inputs , output , gate_type , delay);

                    // Link the inputs to the gate
                    for (auto& input : inputs) {
                        input->addGate (gate);
                    }
                    circuit.addGate (gate);
                }
            }
        }
    }
    return circuit;
}
