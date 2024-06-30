#include "Monster.h"

Monster::Monster(const std::string& name) : name(name) {}

Monster::~Monster() {}

std::string Monster::getName() const {
    return name;
}
