#pragma once
#include <string>

class RunawayPolicy {
public:
    virtual std::string getFullInfo() const = 0;
    virtual ~RunawayPolicy() = default; // Use virtual destructor for polymorphic base class
};
