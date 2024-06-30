#pragma once

#include <string>

class Item {
public:
    Item(const std::string& name);
    virtual ~Item();
    std::string getName() const;
private:
    std::string name;
};
