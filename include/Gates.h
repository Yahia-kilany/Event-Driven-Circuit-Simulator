#ifndef GATES_H
#define GATES_H

#include <vector>
#include <string>
#include "Event.h"
#include "Wire.h"

class Wire; // Forward declaration of Wire class

class Gate {
protected:
    std::vector<Wire*> inputs; // A vector of input wires
    Wire* output;              // Output wire
    int delay;                 // Delay in picoseconds
    std::string type;          // Type of gate

    int getGateType();         // Determines the gate type

public:
    // Constructor to initialize gate with inputs, output, type, and delay
    Gate(std::vector<Wire*> ins, Wire* out, std::string typ, int d = 0) 
        : inputs(ins), output(out), type(typ), delay(d) {}

    // Evaluates the gate and generates an output event
    Event evaluate(Event e);
};
#include "../Src/Gates.cpp"
#endif // GATES_H
