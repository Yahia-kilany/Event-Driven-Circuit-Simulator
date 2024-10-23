#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "circuit.h"
#include "Gates.h"
#ifndef PARSEVERILOG_H
#define PARSEVERILOG_H
using namespace std;


class ParseVerilog {
public:
    ParseVerilog () = default;
    Circuit parse (const std::string& filename); // Change parameter type to const reference
    ~ParseVerilog () = default; // Default destructor
};

#endif //PARSEVERILOG_H