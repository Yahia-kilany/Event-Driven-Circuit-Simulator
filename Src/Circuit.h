#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include "event.h"
#include "Gates.h"

#ifndef CIRCUIT_H
#define CIRCUIT_H

// Define a Wire class to store the value of each wire
class Wire {
public:
    std::string name;
    bool value; // Assuming wire value is of type bool (0 or 1)
    std::vector<Gate*> endGates; // Gates connected to this wire

    Wire(std::string name) : name(name), value(false) {}
};

// Base class for Gates (define your Gate classes inheriting from this)
class Gate {
public:
    virtual event evaluate() = 0; // Pure virtual function to evaluate the gate
    // Other necessary members and methods for gates...
};

// Circuit Class to hold wires and gates
class Circuit {
private:
    std::map<std::string, Wire*> wires;
    std::vector<Gate*> gates;

public:
    // Create a wire and add it to the circuit
    Wire* addWire(std::string name) {
        Wire* w = new Wire(name);
        wires[name] = w;
        return w;
    }

    // Create a gate and add it to the circuit
    void addGate(Gate* gate) {
        gates.push_back(gate);
    }

    // Simulate the circuit by evaluating all gates
    void simulate() {
        std::priority_queue<event, std::vector<event>, CompareEvent> eventQueue;
        std::queue<Gate*> gateQueue;

        while (!eventQueue.empty()) {
            event e = eventQueue.top(); // Access the highest-priority event
            std::cout << e; // Make sure `event` has an overloaded operator<<
            wires[e.getName()]->value = e.getValue(); // Update the wire value
            
            for (Gate* g : wires[e.getName()]->endGates) {
                gateQueue.push(g);
            }

            while (!gateQueue.empty()) {
                Gate* gate = gateQueue.front();
                eventQueue.push(gate->evaluate());
                gateQueue.pop();
            }

            eventQueue.pop(); // Remove the processed event
        }
    }

    // Print the values of all wires in the circuit
    void printValues() {
        for (const auto& pair : wires) {
            std::cout << pair.second->name << ": " << pair.second->value << std::endl;
        }
    }

    // Destructor to free memory (optional, but recommended)
    ~Circuit() {
        for (auto& pair : wires) {
            delete pair.second; // Delete each Wire
        }
        for (Gate* gate : gates) {
            delete gate; // Delete each Gate
        }
    }
};

#endif // CIRCUIT_H