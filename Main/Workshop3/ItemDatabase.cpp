#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "ItemDatabase.h"
#include "Modifier.h"
#include "Monster.h"
#include "Item.h"

void ItemDatabase::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string        type, name, param;
        std::getline(iss, type, ';');
        std::getline(iss, name, ';');
        std::getline(iss, param, ';');

        if (type == "Monster") {
            const uint_fast8_t level = std::stoi(param);
            monsterDeck.addElement(std::make_unique<Monster>(name, level));
        } else if (type == "Modifier") {
            Modifier::EffectFunction effect;
            if (param == "Double_Bonus") {
                effect = [](int& value) { value *= 2; };
            } else if (param == "Add_One") {
                effect = [](int& value) { value += 1; };
            }
            modifierDeck.addElement(std::make_unique<Modifier>(name, effect));
        } else if (type == "Item") {
            const uint_fast8_t bonus = std::stoi(param);
            itemDeck.addElement(std::make_unique<Item>(name, bonus));
        }
    }
}

