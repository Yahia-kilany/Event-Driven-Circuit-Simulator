#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>

class Event {
private:
    int time;              // Time of the event
    std::string name;      // Name of the wire associated with the event
    int value;             // Value (e.g., logic level) of the event

    // Friend function to overload the output stream operator, allowing Event objects to be printed easily
    friend std::ostream& operator<<(std::ostream& os, const Event& e);

public:
    // Overloaded equality operator to compare two Event objects
    bool operator==(const Event& e) {
        return (this->time == e.time && this->name == e.name && this->value == e.value);
    }

    // Structure to compare two Event objects based on time for use in a priority queue
    struct CompareEvent {
        // Comparison operator for min-heap (earliest event has highest priority)
        bool operator()(const Event& e1, const Event& e2) const {
            return e1.time > e2.time;
        }
    };

    // Constructor that initializes the event with time, wire name (moved for efficiency), and value
    Event(int t, std::string str, int val) : time(t), name(std::move(str)), value(val) {}

    // Getters for accessing the event's attributes
    int getValue() const { return value; }                  // Returns the event's value
    int getTime() const { return time; }                    // Returns the event's time
    const std::string& getName() const { return name; }     // Returns a constant reference to the event's name
};
std::ostream& operator<<(std::ostream& os , const Event& e) {
    os << e.time << "," << e.name << "," << e.value<<std::endl;
    return os;
}
#endif // EVENT_H