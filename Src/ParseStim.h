//
// Created by Mahmoud Aly on 10/23/2024.
//
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>
using namespace std;

std::vector<std::map<std::string, int>> parseStimFile(const std::string& filename) {
    std::vector<std::map<std::string, int>> stimuli;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the stimulus file: " << filename << std::endl; //to know if the file is open successfully or not.
        return stimuli;
    }

    std::string line;
    std::regex value_regex(R"((\w+)\s*=\s*(\d+);)");
    std::smatch match;
    std::map<std::string, int> stimulus;

    while (std::getline(file, line)) {
        // Parse input values
        if (std::regex_search(line, match, value_regex)) {
            stimulus[match[1]] = std::stoi(match[2]);
        }
        // End of a time frame, store the current stimulus
        if (line.find("#") != std::string::npos) {
            if (!stimulus.empty()) {
                stimuli.push_back(stimulus);
                stimulus.clear(); // Reset for the next time frame
            }
        }
    }
    // Push the last stimulus
    if (!stimulus.empty()) {
        stimuli.push_back(stimulus);
    }

    file.close();
    return stimuli;
}
