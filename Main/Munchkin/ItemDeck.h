#pragma once

#include <vector>
#include <memory>
#include "Item.h"

class ItemDeck {
public:
    ItemDeck();
    std::unique_ptr<Item> generateItem();

private:
    std::vector<std::unique_ptr<Item>> items;
};
