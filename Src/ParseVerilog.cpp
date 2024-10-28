#include "ParseVerilog.h"

std::string removeCharacters (const std::string& input , const std::string& charsToRemove) {
    std::string result = input;
    result.erase (std::remove_if (result.begin () , result.end () ,
        [&](char c) { return charsToRemove.find (c) != std::string::npos; }) ,
        result.end ());
    return result;
}

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
            char ch;
            iss >> token; // Ignore "module"
            while (iss.get (ch) && ch != '(') {
                moduleName += ch;
            }
            cout << moduleName;
            while (iss >> token) {
                token = removeCharacters (token , charsToRemove);
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

            if ((wireType == "input" || wireType == "output") && wires.find (name) == wires.end ()) {
                std::cerr << "Error: input/output wire " << name << " not declared in header." << std::endl;
            }
            else if (wireType == "wire") {
                Wire* w = circuit.addWire (name);
                w->type = wireType;
                wires[name] = w;
            }
            else {
                wires[name]->type = wireType;
            }
            std::cout << wireType << " : " << name << std::endl;
        }
        else {
            std::string gate_type , gate_name , gate_delay , temp;
            int delay = 0;

            if (line.find ("and") != std::string::npos || line.find ("or") != std::string::npos ||
                line.find ("nand") != std::string::npos || line.find ("nor") != std::string::npos ||
                line.find ("xor") != std::string::npos || line.find ("xnor") != std::string::npos ||
                line.find ("buf") != std::string::npos || line.find ("not") != std::string::npos) {

                iss >> gate_type;
                iss >> temp;
                if (temp[0] == '#') {
                    gate_delay = removeCharacters (temp , charsToRemove);
                    delay = std::stoi (gate_delay);
                    iss >> gate_name;
                }
                else {
                    gate_name = temp;
                }

                std::vector<Wire*> ports;
                while (iss >> token) {
                    if (token != "(" && token != ")" && token != "," && token != ";") {
                        token = removeCharacters (token , charsToRemove);
                        if (wires.find (token) != wires.end ()) {
                            ports.push_back (wires[token]);
                            std::cout << "Gate Port: " << token << std::endl;
                        }
                        else {
                            std::cerr << "Error: Wire " << token << " not found." << std::endl;
                        }
                    }
                }

                if (!ports.empty ()) {
                    Wire* output = ports[0];
                    std::vector<Wire*> inputs (ports.begin () + 1 , ports.end ());
                    Gate* gate = new Gate (inputs , output , gate_type , delay);
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
