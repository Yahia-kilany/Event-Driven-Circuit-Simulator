#include "Gates.h"
#include "Event.h"
int Gate::getGateType () {
    if (type == "and") return 0;
    if (type == "or") return 1;
    if (type == "not") return 2;
    if (type == "nand") return 3;
    if (type == "nor") return 4;
    if (type == "xor") return 5;
    if (type == "xnor") return 6;
    return -1; // Invalid type
}//TODO: turn into an enum
Event Gate::evaluate (Event e) {
    bool result = false; // Default value

    switch (getGateType ()) {
    case 0: // AND
        result = true;
        for (Wire* wire : inputs) {
            result = result && wire->value;
        }
        break;
    case 1: // OR
        result = false;
        for (Wire* wire : inputs) {
            result = result || wire->value;
        }
        break;
    case 2: // NOT
        if (inputs.size () == 1) {
            result = !inputs[0]->value;
        }
        break;
    case 3: // NAND
        result = true;
        for (Wire* wire : inputs) {
            result = result && wire->value;
        }
        result = !result; // Invert for NAND
        break;
    case 4: // NOR
        result = false;
        for (Wire* wire : inputs) {
            result = result || wire->value;
        }
        result = !result; // Invert for NOR
        break;
    case 5: // XOR
        result = inputs[0]->value; // Start with the first value
        for (size_t i = 1; i < inputs.size (); ++i) {
            result = result ^ inputs[i]->value; // XOR with each subsequent input
        }
        break;
    case 6: // XNOR
        result = inputs[0]->value; // Start with the first value
        for (size_t i = 1; i < inputs.size (); ++i) {
            result = result ^ inputs[i]->value; // XOR with each subsequent input
        }
        result = !result; // Invert for XNOR
        break;
    default:
        break;
    }
    Event* output = new Event (e.getTime () + delay , this->output->name , result);
    return *output;// Return the output value
}