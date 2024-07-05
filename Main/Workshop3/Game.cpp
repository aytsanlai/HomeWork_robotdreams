#include "Game.h"
#include "Item.h"
#include "Monster.h"
#include "RunawayPolicy.h"
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

uint_fast8_t Game::getPlayerLevel() const {
    return playerLevel;
}

void Game::addPlayerLevel(uint_fast8_t level) {
    playerLevel += level;
}

uint_fast8_t Game::getPower() const {
    return playerLevel + ( equippedItem ? equippedItem->getBonus() : 0 );
//    return std::accumulate(itemHand.begin(), itemHand.end(), playerLevel, [](uint_fast8_t sum, const std::unique_ptr<Item>& item) {
//        return sum + item->getBonus();
//    });
}

bool Game::fightMonster(const std::unique_ptr<Monster>& monster) {
    static thread_local std::mt19937 rng(std::random_device{}());
    if (monster->getLevel() <= getPower()) {
        std::cout << "You've defeated the monster!\n";
        addPlayerLevel(monster->getLevel());
        return true;
    } else {
        std::cout << "You are trying flee and roll your dice.\n";
        std::uniform_int_distribution<uint_fast8_t> fleeDist(1, 6);
        uint_fast8_t const                          fleeRoll = fleeDist(rng);
        std::cout << "You've rolled a " << +fleeRoll << ".\n";
        if (fleeRoll > 4) {
            std::cout << "You've successfully fled!\n";
            std::uniform_int_distribution<uint_fast8_t> runawayDist(1, 3);
            uint_fast8_t const                          runawayRoll = runawayDist(rng);
            std::unique_ptr<RunawayPolicy>              policy;
            if (runawayRoll == 1) {
                policy = std::make_unique<Runaway_ItemEquippedRemoval>();
            } else if (runawayRoll == 2) {
                policy = std::make_unique<Runaway_ModifierFromHandRemoval>();
            } else {
                policy = std::make_unique<Runaway_BiggestBonusCardRemoval>();
            }
            std::cout << policy->getFullInfo() << std::endl;
            policy->apply(*this);
        } else {
            std::cout << "You died.\n";
        }
    }
    return false;
}


bool Game::equipItem(uint_fast8_t index) {
    if (index >= itemHand.size()) {
        std::cout << "Invalid item index\n";
        return false;
    }
    equippedItem = std::move(itemHand[index]);
    itemHand.erase(itemHand.begin() + index);
    std::cout << "Equipped item: " << equippedItem->getName() << std::endl;
    return true;
}

void Game::removeEquippedItem() {
    if (!equippedItem) {
        std::cout << "Tried to remove an equipped item, but there was none.\n";
        return;
    }
    std::cout << "Removed equipped item: " << equippedItem->getName() << std::endl;
    if (equippedItem) equippedItem.reset();
}

void Game::removeRandomModifierFromHand() {
    if (modifierHand.empty()) {
        std::cout << "Tried to remove a modifier from your hand, but there was none.\n";
        return;
    }
    static thread_local std::mt19937      rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, modifierHand.size() - 1);
    size_t const                          index = dist(rng);
    std::cout << "Removed modifier from hand: " << modifierHand[index]->getName() << std::endl;
    modifierHand.erase(modifierHand.begin() + index);
}

void Game::removeBiggestBonusCard() {
    if (itemHand.empty()) {
        std::cout << "Tried to remove the biggest bonus card, but there was none.\n";
        return;
    }
    auto it = std::max_element(itemHand.begin(), itemHand.end(),
                               [](const std::unique_ptr<Item>& a, const std::unique_ptr<Item>& b) {
                                   return a->getBonus() < b->getBonus();
                               });
    std::cout << "Removed the biggest bonus card: " << ( *it )->getName() << " (Bonus: " << +( *it )->getBonus()
              << ")\n";
    itemHand.erase(it);
}

void Game::drawCard(const bool looting = false) {
    std::vector<size_t> deckSizes = { itemDatabase.monsterDeck.size(), itemDatabase.modifierDeck.size(),
                                      itemDatabase.itemDeck.size() };

    size_t const totalSize = std::accumulate(deckSizes.begin(), deckSizes.end(), 0UL);
    if (totalSize == 0) {
        std::cout << "All decks are empty" << std::endl;
        return;
    }

    static thread_local std::mt19937      rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, totalSize - 1);
    size_t const                          index = dist(rng);

    if (index < deckSizes[0]) {
        auto monster = itemDatabase.monsterDeck.generateElement();
        std::cout << "Drew a Monster: " << monster->getName() << " (Level " << +monster->getLevel() << ")\n";
        if (looting) {
            monsterHand.emplace_back(std::move(monster));
        } else {
            fightMonster(monster);
        }
    } else if (index < deckSizes[0] + deckSizes[1]) {
        auto modifier = itemDatabase.modifierDeck.generateElement();
        std::cout << "Drew a Modifier: " << modifier->getName() << std::endl;
        modifierHand.emplace_back(std::move(modifier));
    } else {
        auto item = itemDatabase.itemDeck.generateElement();
        std::cout << "Drew an Item: " << item->getName() << std::endl;
        itemHand.emplace_back(std::move(item));
    }
}

void Game::start() {
    std::cout << "Starting the game..." << std::endl;
    while (getPlayerLevel() < 20) {
        std::cout << "You kick down the door.\n";
        drawCard();
        printState();
        bool alreadyLooted = false;
        while (true) {
            std::cout << std::endl << "Select a card, (L)oot the room or (E)nd your turn: ";
            std::string input;
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Invalid input\n";
                continue;
            }

            std::istringstream iss(input);

            char action;
            iss >> action;

            switch (toupper(action)) {
                case 'T': {
                    unsigned int index;
                    if (iss >> index) {
                        if (index >= monsterHand.size()) {
                            std::cout << "Invalid monster index\n";
                            continue;
                        }
                        if (fightMonster(monsterHand[index])) monsterHand.erase(monsterHand.begin() + index);
                    } else {
                        std::cout << "Invalid index\n";
                    }
                    break;
                }
                case 'I': {
                    unsigned int index;
                    if (iss >> index) {
                        equipItem(static_cast<uint_fast8_t>(index));
                    } else {
                        std::cout << "Invalid index\n";
                        continue;
                    }
                    break;
                }
                case 'M': {
                    std::cout << "Modifiers aren't fully supported yet\n";
                    continue;
                }
                case 'L': {
                    if (alreadyLooted) {
                        std::cout << "You've already looted the room\n";
                        continue;
                    }
                    drawCard(true);
                    alreadyLooted = true;
                    printState();
                    continue;
                }
                case 'E': {
                    break;
                }
                default: {
                    std::cout << "Invalid action\n";
                    continue;
                }
            }
            break;
        }
        std::cout << std::flush;
    }
    std::cout << "Game over!" << std::endl;
}

void Game::printState() const {
    std::cout << "Player level: " << +getPlayerLevel() << "\n";
    if (!monsterHand.empty()) {
        std::cout << " --- Monsters ---\n";
        for (size_t i = 0; i < monsterHand.size(); i++)
            std::cout << "T" << i << ": " << monsterHand[i]->getName()
                      << " (Level " << +monsterHand[i]->getLevel() << ")\n";

    }
    if (!modifierHand.empty()) {
        std::cout << " --- Modifiers ---\n";
        for (size_t i = 0; i < modifierHand.size(); i++)
            std::cout << "M" << i << ": " << modifierHand[i]->getName() << "\n";

    }
    if (!itemHand.empty()) {
        std::cout << " --- Items ---\n";
        for (size_t i = 0; i < itemHand.size(); i++)
            std::cout << "I" << i << ": " << itemHand[i]->getName() << " (Bonus: " << +itemHand[i]->getBonus() << ")\n";
    }
    if (equippedItem)
        std::cout << "Equipped item: " << equippedItem->getName() << " (Bonus: " << +equippedItem->getBonus() << ")\n";

    std::cout << std::flush;
}
