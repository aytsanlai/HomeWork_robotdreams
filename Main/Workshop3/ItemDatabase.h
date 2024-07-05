#pragma once

#include <string>
#include "Monster.h"
#include "Modifier.h"
#include "DeckBase.h"
#include "Item.h"

class ItemDatabase {
public:
    explicit ItemDatabase(const std::string& filename) {
        loadFromFile(filename);
    }

    DeckBase<Monster> monsterDeck;
    DeckBase<Modifier> modifierDeck;
    DeckBase<Item> itemDeck;

private:
    void loadFromFile(const std::string& filename);
};
