#ifndef PARSEVERILOG_H
#define PARSEVERILOG_H

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Circuit.h"
#include "Gates.h"

// Use the standard namespace to simplify code readability
using namespace std;

/**
 * Utility function to remove specified characters from a string.
 * @param input The original string.
 * @param charsToRemove A string of characters to remove from the input.
 * @return A new string with the specified characters removed.
 */
std::string removeCharacters(const std::string& input, const std::string& charsToRemove) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(),
        [&](char c) { return charsToRemove.find(c) != std::string::npos; }),
        result.end());
    return result;
}

/**
 * Class for parsing a Verilog file to extract circuit information.
 */
class ParseVerilog {
private:
    std::string filename;  // The filename of the Verilog file to parse

public:
    ParseVerilog() = default;   // Default constructor
    /**
     * Parses a Verilog file to build and return a Circuit object.
     * @param filename The name of the Verilog file to parse.
     * @return Circuit object containing wires and gates parsed from the file.
     */
    Circuit parse(const std::string& filename);

    ~ParseVerilog() = default;  // Default destructor
};

// Include the implementation file
#include "ParseVerilog.cpp"

#endif //PARSEVERILOG_H
