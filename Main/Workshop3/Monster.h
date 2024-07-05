#pragma once

#include <string>

class Monster {
public:
    Monster(std::string name, uint_fast8_t level);
    virtual ~Monster();
    std::string getName() const;
    uint_fast8_t getLevel() const;
private:
    std::string name;
    uint_fast8_t level;
};
