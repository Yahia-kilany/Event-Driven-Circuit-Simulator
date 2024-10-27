#include <vector>
#include <string>
#include "event.h"

#ifndef GATES_H
#define GATES_H

// Define a Wire class to store the value of each wire
class Wire {
public:
    bool value;
    std::string type;
    std::string name;
    std::vector<Gate*> endGates;

    Wire(std::string n, Gate* g) : name(n), value(false) {}
    void addGate(Gate* g) {
        endGates.push_back(g);
    }
};
class Gate {
protected:
    std::vector<Wire*> inputs; // A vector of input wires
    Wire* output;              // Output wire
    int delay;            // Delay in ns
    std::string type;          // Type of gate
    int getGateType();

public:
    Gate(std::vector<Wire*> ins, Wire* out,std::string typ, int d=0) : inputs(ins), output(out),type(typ),delay(d) {}
    event evaluate(event e);

    };
#endif //GATES_H