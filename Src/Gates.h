#include <vector>
#include <string>
#ifndef GATES_H
#define GATES_H
// Define a Wire class to store the value of each wire
class Wire {
public:
    bool value;
    std::string type;
    std::string name;

    Wire(std::string n) : name(n), value(false) {}
};
class Gate {
protected:
    std::vector<Wire*> inputs; // A vector of input wires
    Wire* output;              // Output wire
    std::string type;          // Type of gate
    int getGateType();

public:
    Gate(std::vector<Wire*> ins, Wire* out,std::string typ) : inputs(ins), output(out),type(typ) {}
    bool evaluate();

    };
#endif //GATES_H