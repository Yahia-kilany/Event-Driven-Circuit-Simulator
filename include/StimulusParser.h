// StimulusParser.h
#ifndef STIMULUSPARSER_H
#define STIMULUSPARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Event.h"
#include "ParseVerilog.h"

std::vector<Event> parseStim(const std::string& filename);
#include "../Src/StimulusParser.cpp"
#endif // STIMULUSPARSER_H