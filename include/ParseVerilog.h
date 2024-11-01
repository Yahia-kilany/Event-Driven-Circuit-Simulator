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
std::string removeCharacters (const std::string& input , const std::string& charsToRemove) {
    std::string result = input;
    result.erase (std::remove_if (result.begin () , result.end () ,
        [&](char c) { return charsToRemove.find (c) != std::string::npos; }) ,
        result.end ());
    return result;
}



Circuit parseVerilog (const std::string& filename);

// Include the implementation file
#include "../Src/ParseVerilog.cpp"
#endif //PARSEVERILOG_H
