#include <iostream>
#include "Gates.h"
#include "Circuit.h"
#include "ParseVerilog.h"
#include "Event.h"
#include "StimulusParser.h"

std::ostream& operator<<(std::ostream& os , const Event& e) {
    os << "#" << e.time << " " << e.name << " " << e.value<<endl;
    return os;
}
int main () {
    ParseVerilog parser;
    Circuit circuit = parser.parse ("../Tests/parity_checker.v");
    circuit.simulate ();
    vector<Event> events = parseStimFile ("../Tests/parity_checker.stim");
    circuit.fillEventQueue (events);
    circuit.simulate ();

    return 0;
}

