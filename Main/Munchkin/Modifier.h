#pragma once

#include <string>

class Modifier {
public:
    explicit Modifier(const std::string& name) : name(name) {}
    const std::string& getName() const { return name; }

private:
    std::string name;
    std::string getName() const;
};
