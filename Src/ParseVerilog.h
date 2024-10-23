#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "circuit.h"
#include "Gates.h"
using namespace std;
std::string removeCharacters (const std::string& input , const std::string& charsToRemove) {
    std::string result = input; // Copy the input string to result

    // Use std::remove_if and erase to remove unwanted characters
    result.erase (std::remove_if (result.begin () , result.end () ,
        [&](char c) { return charsToRemove.find (c) != std::string::npos; }) ,
        result.end ());

    return result; // Return the modified string
}

class ParseVerilog {
public:
    ParseVerilog () = default;
    Circuit parse (const std::string& filename); // Change parameter type to const reference
    ~ParseVerilog () = default; // Default destructor
};

