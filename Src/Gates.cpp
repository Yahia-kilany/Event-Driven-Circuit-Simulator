#include "../include/Gates.h"
#include "../include/Wire.h"

// Returns an integer representing the gate type based on the type string.
// TODO: This function should ideally be replaced with an enum.
int Gate::getGateType() {
    if (type == "and") return 0;
    if (type == "or") return 1;
    if (type == "not") return 2;
    if (type == "nand") return 3;
    if (type == "nor") return 4;
    if (type == "xor") return 5;
    if (type == "xnor") return 6;
    if (type == "buf") return 7; // Buffer (BUF) gate type
    return -1; // Invalid type
}

// Evaluates the gate based on its type and input wires, then generates an output event
Event Gate::evaluate(Event e) {
    bool result = false; // Initialize result to default (false)

    // Determine the gate's output based on its type
    switch (getGateType()) {
    case 0: // AND Gate
        result = true;
        for (Wire* wire : inputs) {
            result = result && wire->value; // AND of all input wire values
        }
        break;
    case 1: // OR Gate
        result = false;
        for (Wire* wire : inputs) {
            result = result || wire->value; // OR of all input wire values
        }
        break;
    case 2: // NOT Gate
        if (inputs.size() == 1) {
            result = !inputs[0]->value; // Invert the single input
        }
        break;
    case 3: // NAND Gate
        result = true;
        for (Wire* wire : inputs) {
            result = result && wire->value; // AND of all input wire values
        }
        result = !result; // Invert the result for NAND
        break;
    case 4: // NOR Gate
        result = false;
        for (Wire* wire : inputs) {
            result = result || wire->value; // OR of all input wire values
        }
        result = !result; // Invert the result for NOR
        break;
    case 5: // XOR Gate
        result = inputs[0]->value;
        for (size_t i = 1; i < inputs.size(); ++i) {
            result = result ^ inputs[i]->value; // XOR operation on all inputs
        }
        break;
    case 6: // XNOR Gate
        result = inputs[0]->value;
        for (size_t i = 1; i < inputs.size(); ++i) {
            result = result ^ inputs[i]->value; // XOR operation
        }
        result = !result; // Invert the result for XNOR
        break;
    case 7: // BUF (Buffer) Gate
        if (inputs.size() == 1) {
            result = inputs[0]->value; // Pass the input value directly to the output
        }
        break;
    default:
        break; // If an invalid gate type, do nothing
    }

    // Create a new event for the output wire, scheduled after the gate's delay
    Event* output = new Event(e.getTime() + delay, this->output->name, result);
    return *output;
}
