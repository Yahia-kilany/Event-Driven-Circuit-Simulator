#include <iostream>
#include "../include/Gates.h"
#include "../include/Circuit.h"
#include "../include/ParseVerilog.h"
#include "../include/StimulusParser.h"

std::ostream& operator<<(std::ostream& os , const Event& e) {
    os << e.time << " " << e.name << " " << e.value<<endl;
    return os;
}
int main () {
    Circuit circuit = parseVerilog ("../Tests/parity_checker.v");
    circuit.simulate ();
    vector<Event> events = parseStimFile ("../Tests/parity_checker.stim");
    circuit.fillEventQueue (events);
    circuit.simulate ();

    return 0;
}

