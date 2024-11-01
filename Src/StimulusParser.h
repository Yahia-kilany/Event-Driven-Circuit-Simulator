// StimulusParser.h
#ifndef STIMULUSPARSER_H
#define STIMULUSPARSER_H

#include <vector>
#include <string>
#include "Event.h"

std::vector<Event> parseStimFile(const std::string& filename);
#include "StimulusParser.cpp"
#endif // STIMULUSPARSER_H