// Gate.h
#ifndef GATE_H
#define GATE_H

#include <string>
#include <vector>

struct Wire {
    std::string name;
    bool value;
};

class Gate {
protected:
    std::vector<Wire*> inputs; // Pointer to Wire objects for inputs
    Wire* output; // Pointer to a Wire object for the output

public:
    virtual void evaluate() = 0; // Evaluate the gate's output based on inputs

    void setInputs(const std::vector<Wire*>& inputs) { this->inputs = inputs; }
    void setOutput(Wire* output) { this->output = output; }
};

class ANDGate : public Gate {
public:
    void evaluate() override; // Override the evaluate method
};

class ORGate : public Gate {
public:
    void evaluate() override; // Override the evaluate method
};

class XORGate : public Gate {
public:
    void evaluate() override; // Override the evaluate method
};

class NANDGate : public Gate {
public:
    void evaluate() override; // Override the evaluate method
};

class NORGate : public Gate {
public:
    void evaluate() override; // Override the evaluate method
};

class XNORGate : public Gate {
public:
    void evaluate() override; // Override the evaluate method
};

class BUFGate : public Gate {
public:
    void evaluate() override; // Override the evaluate method
};

#endif // GATE_H