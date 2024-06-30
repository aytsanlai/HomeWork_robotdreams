#include "Item.h"

Item::Item(const std::string& name) : name(name) {}

Item::~Item() {}

std::string Item::getName() const {
    return name;
}
