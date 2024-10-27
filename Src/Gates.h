#ifndef GATES_H
#define GATES_H
#include <vector>
#include <string>
#include "event.h"
#include "wire.h"

class Wire;
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
#include "Gates.cpp"
#endif //GATES_H