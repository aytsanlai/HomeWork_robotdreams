#include "Modifier.h"

Modifier::Modifier(const std::string& name) : name(name) {}

Modifier::~Modifier() {}

std::string Modifier::getName() const {
    return name;
}
