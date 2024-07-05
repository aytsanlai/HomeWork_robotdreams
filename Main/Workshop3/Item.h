#pragma once

#include <string>

class Item {
public:
    Item(std::string name, uint_fast8_t bonus);
    virtual ~Item();
    std::string getName() const;
    uint_fast8_t getBonus() const;
private:
    std::string name;
    uint_fast8_t bonus;
};
