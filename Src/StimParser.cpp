#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Event.h"
std::string removeCharacters (const std::string& input , const std::string& charsToRemove) {
    std::string result = input;
    result.erase (std::remove_if (result.begin () , result.end () ,
        [&](char c) { return charsToRemove.find (c) != std::string::npos; }) ,
        result.end ());
    return result;
}
std::vector<Event> parseStimFile (const std::string& filename) {
    std::string charstoRemove = "# ";
    std::vector<Event> events;
    std::ifstream file (filename);

    if (!file.is_open ()) {
        std::cerr << "Error: Could not open the stimulus file: " << filename << std::endl;
        return events;
    }

    std::string line;

    while (std::getline (file , line)) {
        std::istringstream iss (line);
        std::string token;
        iss >> token;
        token = removeCharacters(token , charstoRemove);
        int time = std::stoi (token);
        getline (iss , token , '=');
        token = removeCharacters (token , charstoRemove);
        std::string wire_name = token;
        getline (iss , token , ';');
        token = removeCharacters (token , charstoRemove);
        int value = std::stoi (token);
        Event event (time , wire_name , value);
        events.push_back (event);
    }
    return events;
}
void printEvents (const std::vector<Event>& events) {
    for (const auto& event : events) {
        std::cout<<event<<std::endl;

    }
}
