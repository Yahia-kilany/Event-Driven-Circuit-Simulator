#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <string>
class Event {
private:
    int time;
    std::string name;
    int value;
    
    // Declare CompareEvent and the output operator as friends for access to private members
    friend std::ostream& operator<<(std::ostream& os, const Event& e);
    friend struct CompareEvent;

public:
    // Constructor using move semantics for the string
    Event(int t, std::string str, int val) : time(t), name(std::move(str)), value(val) {}

    // Getters
    int getValue() const { return value; }
    int getTime() const { return time; }
    const std::string& getName() const { return name; }
};



// Comparison struct for event
struct CompareEvent {
    bool operator()(const Event &e1, const Event &e2) const {
        return e1.time > e2.time; // For min-heap
    }
};
#endif //EVENT_H