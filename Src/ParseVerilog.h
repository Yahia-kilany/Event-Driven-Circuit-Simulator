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
using namespace std;

std::string removeCharacters (const std::string& input , const std::string& charsToRemove) {
    std::string result = input;
    result.erase (std::remove_if (result.begin () , result.end () ,
        [&](char c) { return charsToRemove.find (c) != std::string::npos; }) ,
        result.end ());
    return result;
}

class ParseVerilog {
private:
    std::string filename;
public:
    ParseVerilog () = default;
    Circuit parse (const std::string& filename); // Change parameter type to const reference
    ~ParseVerilog () = default; // Default destructor
};

#include "ParseVerilog.cpp"
#endif //PARSEVERILOG_H