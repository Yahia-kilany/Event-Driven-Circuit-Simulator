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
        if (line[0] == '#') {
            if (current_time != 0) {
                events.push_back({current_time, current_values});
            }
            current_time = std::stoi(line.substr(1));
            continue;
        }

        std::istringstream iss(line);
        std::string wire_name;
        char equals;
        int value;

        if (iss >> wire_name >> equals >> value && equals == '=') {
            current_values[wire_name] = value;
        }
    }

    if (current_time != 0) {
        events.push_back({current_time, current_values});
    }

    file.close();
    return events;
}

void printEvents(const std::vector<Event>& events) {
    for (const auto& event : events) {
        std::cout << "At time " << event.time << ": ";
        for (const auto& value : event.values) {
            std::cout << value.first << " = " << value.second << ", ";
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
