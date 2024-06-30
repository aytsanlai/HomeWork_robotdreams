#include "ModifierDeck.h"
#include <random>

ModifierDeck::ModifierDeck() {
    // Adding one modifier to the deck for demonstration
    modifiers.push_back(std::make_unique<Modifier>("Modifier1"));
}

std::unique_ptr<Modifier> ModifierDeck::generateModifier() {
    if (modifiers.empty()) return nullptr;

    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, modifiers.size() - 1);

    size_t index = dist(rng);
    std::unique_ptr<Modifier> modifier = std::move(modifiers[index]);
    modifiers.erase(modifiers.begin() + index);
    return modifier;
}
