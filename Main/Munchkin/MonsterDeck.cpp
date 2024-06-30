#include "MonsterDeck.h"
#include <random>
#include <algorithm>

MonsterDeck::MonsterDeck() {
    // Adding one monster to the deck for demonstration
    monsters.push_back(std::make_unique<Monster>("Monster1"));
}

std::unique_ptr<Monster> MonsterDeck::generateMonster() {
    if (monsters.empty()) return nullptr;

    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, monsters.size() - 1);

    size_t index = dist(rng);
    std::unique_ptr<Monster> monster = std::move(monsters[index]);
    monsters.erase(monsters.begin() + index);
    return monster;
}
