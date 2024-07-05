#include "Item.h"

#include <utility>

Item::Item(std::string name, const uint_fast8_t bonus) : name(std::move(name)), bonus(bonus) {}

Item::~Item() = default;

std::string Item::getName() const {
    return name;
}

uint_fast8_t Item::getBonus() const {
    return bonus;
}