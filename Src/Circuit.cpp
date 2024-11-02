#include "../include/Circuit.h"
namespace fs = std::filesystem;

// Adds an event to the event queue
void Circuit::addEvent (Event e) {
    eventQueue.push (e);
}

// Adds a new wire to the circuit, assigns it a name, and returns a pointer to it
Wire* Circuit::addWire (std::string name) {
    Wire* w = new Wire (name);
    wires[name] = w;
    return w;
}

// Fills the event queue with a list of initial events
void Circuit::fillEventQueue (const std::vector<Event>& events) {
    for (const Event& e : events) {
        addEvent (e);
    }
}

// Adds a gate to the circuit, stores it in the gates vector
void Circuit::addGate (Gate* gate) {
    gates.push_back (gate);
}

void Circuit::simulate() {
    std::string outputDir = "../output/";

    // Create the output directory if it does not exist
    if (!fs::exists(outputDir)) {
        fs::create_directory(outputDir);
        std::cout << "Created output directory: " << outputDir << std::endl;
    }

    std::string outputFileName = moduleName + ".sim";
    std::string outputPath = outputDir + outputFileName;
    std::ofstream outFile(outputPath);
    
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open the output file " << outputPath << std::endl;
        return;
    }

    std::queue<Gate*> gateQueue; // Queue to manage gates affected by current events

    // Process each event until the event queue is empty
    while (!eventQueue.empty()) {
        Event e = eventQueue.top(); // Get the next event
        eventQueue.pop();
        if(!(e==eventQueue.top())||eventQueue.empty()){
        outFile << e; // Always log the event
        }
        // Update the wire associated with this event
        wires[e.getName()]->value = e.getValue();

        // Push all gates connected to this wire into the gate queue for evaluation
        for (Gate* g : wires[e.getName()]->endGates) {
            gateQueue.push(g);
        }

        // Evaluate each gate in the gate queue and add the resulting events to the event queue
        while (!gateQueue.empty()) {
            Gate* gate = gateQueue.front();
            eventQueue.push(gate->evaluate(e));
            gateQueue.pop();
        }
    }
}


void Circuit::setModuleName (const std::string& name) {
    moduleName = name;
}
// Prints the current values of all wires in the circuit
void Circuit::printValues () {
    for (const auto& pair : wires) {
        std::cout << pair.second->name << ": " << pair.second->value << std::endl;
    }
}

// Destructor: Cleans up dynamically allocated wires and gates
Circuit::~Circuit () {
    for (auto& pair : wires) {
        delete pair.second;
    }
    for (Gate* gate : gates) {
        delete gate;
    }
}
