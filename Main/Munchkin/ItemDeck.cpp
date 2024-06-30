#include "ItemDeck.h"
#include <random>
#include <algorithm>

ItemDeck::ItemDeck() {
    // Adding one item to the deck for demonstration
    items.push_back(std::make_unique<Item>("Item1"));
}

std::unique_ptr<Item> ItemDeck::generateItem() {
    if (items.empty()) return nullptr;

    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, items.size() - 1);

    size_t index = dist(rng);
    std::unique_ptr<Item> item = std::move(items[index]);
    items.erase(items.begin() + index);
    return item;
}
