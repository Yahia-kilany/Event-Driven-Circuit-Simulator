
#include <iostream>
#include <vector>
#include <string>
#include "Gates.h"
#ifndef CIRCUIT_H
#define CIRCUIT_H
// Define a Wire class to store the value of each wire


// Base class for Gates


// Circuit Class to hold wires and gates
class Circuit {
private:
    std::vector<Wire*> wires;
    std::vector<Gate*> gates;

public:
    // Create a wire and add it to the circuit
    Wire* addWire(std::string name) {
        Wire* w = new Wire(name);
        wires.push_back(w);
        return w;
    }

    // Create a gate and add it to the circuit
    void addGate(Gate* gate) {
        gates.push_back(gate);
    }

    // Simulate the circuit by evaluating all gates
    void simulate() {
        for (Gate* gate : gates) {
            gate->evaluate();
        }
    }

    // Print the values of all wires in the circuit
    void printValues() {
        for (Wire* wire : wires) {
            std::cout << wire->name << ": " << wire->value << std::endl;
        }
    }
};

#endif //CIRCUIT_H