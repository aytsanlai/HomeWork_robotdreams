#include "Monster.h"

#include <utility>

Monster::Monster(std::string name, const uint_fast8_t level) : name(std::move(name)), level(level) {}

Monster::~Monster() = default;

std::string Monster::getName() const {
    return name;
}

uint_fast8_t Monster::getLevel() const {
    return level;
}