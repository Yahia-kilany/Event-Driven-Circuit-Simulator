#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <fstream>
#include "Event.h"
#include "Gates.h"

// Circuit class manages wires, gates, and events in the circuit simulation
class Circuit {
private:
    std::map<std::string, Wire*> wires; // Maps wire names to Wire pointers for easy access by name
    std::priority_queue<Event, std::vector<Event>, Event::CompareEvent> eventQueue; // Priority queue for managing events
    std::vector<Gate*> gates; // Vector holding pointers to all gates in the circuit
    std::string moduleName; // Name of the module being simulated
    void addEvent(Event e); // Adds an event to the event queue

public:
    Wire* addWire(std::string name); // Adds a new wire to the circuit and returns a pointer to it
    void fillEventQueue(const std::vector<Event>& events); // Fills the event queue with a list of initial events
    void addGate(Gate* gate); // Adds a gate to the circuit
    void simulate(); // Simulates the circuit by processing events from the event queue
    void setModuleName(const std::string& name); // Sets the name of the module being simulated
    void printValues(); // Prints the current values of all wires in the circuit
    ~Circuit(); // Destructor: Cleans up dynamically allocated wires and gates
};
#include "../Src/Circuit.cpp"
#endif // CIRCUIT_H