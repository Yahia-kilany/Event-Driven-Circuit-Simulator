// StimulusParser.cpp
#include "../include/StimulusParser.h"
/**
 * Parses a stimulus file to generate a list of events for circuit simulation.
 * @param filename The name of the stimulus file to parse.
 * @return A vector of Event objects created based on the file contents.
 */
std::vector<Event> parseStimFile(const std::string& filename) {
    std::string charstoRemove = "# ";  // Characters to remove from the parsed tokens
    std::vector<Event> events;  // Vector to store generated events
    std::ifstream file(filename);  // Open the stimulus file

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the stimulus file: " << filename << std::endl;
        return events;
    }

    std::string line;

    // Read each line in the stimulus file
    while (std::getline(file, line)) {
        std::istringstream iss(line);  // String stream for parsing each line
        std::string token;

        // Parse the time
        iss >> token;
        token = removeCharacters(token, charstoRemove);  // Remove unwanted characters
        int time = std::stoi(token);  // Convert time string to integer

        // Parse the wire name
        getline(iss, token, '=');
        token = removeCharacters(token, charstoRemove);
        std::string wire_name = token;

        // Parse the value
        getline(iss, token, ';');
        token = removeCharacters(token, charstoRemove);
        int value = std::stoi(token);  // Convert value string to integer

        // Create an Event object and add it to the events vector
        Event event(time, wire_name, value);
        events.push_back(event);
    }
    
    return events;  // Return the list of events
}