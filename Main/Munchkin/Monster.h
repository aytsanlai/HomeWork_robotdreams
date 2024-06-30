#pragma once

#include <string>

class Monster {
public:
    Monster(const std::string& name);
    virtual ~Monster();
    std::string getName() const;
private:
    std::string name;
};
