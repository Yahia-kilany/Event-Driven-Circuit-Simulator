#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

struct Event {
    int time;
    std::map<std::string, int> values;
};

std::vector<Event> parseStimFile(const std::string& filename) {
    std::vector<Event> events;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the stimulus file: " << filename << std::endl;
        return events;
    }

    std::string line;
    int current_time = 0;
    std::map<std::string, int> current_values;

    while (std::getline(file, line)) {
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;

        line = line.substr(start);

        if (line[0] == '#') {
            if (current_time != 0) {
                events.push_back({current_time, current_values});
            }
            current_time = std::stoi(line.substr(1));
            current_values.clear();
            continue;
        }

        size_t equals_pos = line.find('=');
        if (equals_pos != std::string::npos) {
            std::string wire_name = line.substr(0, equals_pos);
            int value = std::stoi(line.substr(equals_pos + 1));

            if (value > 0 && line.back() == ';') {
                value = value;
            }

            current_values[wire_name] = value;
        }
    }

    if (current_time != 0 && !current_values.empty()) {
        events.push_back({current_time, current_values});
    }

    file.close();
    return events;
}

void printEvents(const std::vector<Event>& events) {
    for (const auto& event : events) {
        std::cout << "At time " << event.time << ": ";
        for (const auto& [key, val] : event.values) {
            std::cout << key << " = " << val << ", ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string stim_file = "C:/Users/maly8/Desktop/Courses/Digital Design/parser_2.0/parity_checker_rewritten.stim";
    std::vector<Event> events = parseStimFile(stim_file);
    printEvents(events);
    return 0;
}
