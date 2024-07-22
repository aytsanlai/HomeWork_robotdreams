#include "Modifier.h"

#include <utility>

Modifier::Modifier(std::string name, EffectFunction effect) : name(std::move(name)), effect(std::move(effect)) {}

Modifier::~Modifier() = default;

std::string Modifier::getName() const {
    return name;
}

void Modifier::applyEffect(int& value) const {
    effect(value);
}