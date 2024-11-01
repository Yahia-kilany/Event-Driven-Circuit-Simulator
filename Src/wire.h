#ifndef WIRE_H
#define WIRE_H
#include "Gates.h"
#include <vector>
#include <string>
class Gate;
// Wire struct representing a wire in the circuit
struct Wire {
    bool value;                  // Current value of the wire (true or false)
    std::string type;           // Type of the wire (e.g., input, output, or just a connection wire.)
    std::string name;           // Name of the wire
    std::vector<Gate*> endGates; // List of gates connected to this wire

    // Constructor to initialize a wire with its name and default value
    Wire(std::string n) : name(n), value(false) {}

    // Method to add a gate to the wire's list of connected gates
    void addGate(Gate* g) {
        endGates.push_back(g);
    }
};

#endif // WIRE_H