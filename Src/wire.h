#ifndef WIRE_H
#define WIRE_H
#include "Gates.h"
#include <vector>
#include <string>
class Gate;
class Wire {
public:
    bool value;
    std::string type;
    std::string name;
    std::vector<Gate*> endGates;

    Wire(std::string n) : name(n), value(false) {}
    void addGate(Gate* g) {
        endGates.push_back(g);
    }
};
#endif //WIRE_H