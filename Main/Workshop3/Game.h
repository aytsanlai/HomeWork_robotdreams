#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "ItemDatabase.h"
#include "Monster.h"
#include "Modifier.h"
#include "Item.h"

class Game {
public:
    void start();
    void drawCard(bool);
    bool equipItem(uint_fast8_t index);
    void removeEquippedItem();
    void removeRandomModifierFromHand();
    void removeBiggestBonusCard();

    uint_fast8_t getPlayerLevel() const;
    void addPlayerLevel(uint_fast8_t level);
    uint_fast8_t getPower() const;
private:
    bool fightMonster(const std::unique_ptr<Monster>& monster);

    uint_fast8_t playerLevel = 1;
    ItemDatabase itemDatabase = ItemDatabase("database.txt");
    std::unique_ptr<Item>                  equippedItem;
    std::vector<std::unique_ptr<Monster>>  monsterHand;
    std::vector<std::unique_ptr<Modifier>> modifierHand;
    std::vector<std::unique_ptr<Item>>     itemHand;

    void printState() const;
};
